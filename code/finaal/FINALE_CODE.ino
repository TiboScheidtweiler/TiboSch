#include <QTRSensors.h>
#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "iotroam";
const char* password = "LDgsdJd8";

WebServer server(80); // Webserver op poort 80

// QTR-8A sensor setup
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

// Motor driver pins
const int PWMA = 3;  // Left motor PWM
const int AIN1 = 6;  // Left motor direction
const int AIN2 = 5;  // Left motor direction

const int PWMB = 4;  // Right motor PWM
const int BIN1 = 7;  // Right motor direction
const int BIN2 = 8;  // Right motor direction

const int STBY = 9;  // Standby pin

// Physical button pins
const int START_STOP_BUTTON = 12;  // Start/Stop button
const int CALIBRATE_BUTTON = 11;   // Calibration button

// LED pin
const int STATUS_LED = LED_BUILTIN;

// PID constants
float Kp = 1.05;
float Ki = 0.0;
float Kd = 0.0;

int baseSpeed = 120;  // Base speed for the motors
int maxSpeed = 250;   // Maximum motor speed
float reverseFactor = 85; // Factor for reverse speed in tight turns

float lastError = 0;
float integral = 0;

bool isRunning = false;  // Start knop status
unsigned long lastBlinkTime = 0;  // Voor LED-knipperen
bool ledState = false;  // Status van knipperende LED

void setup() {
  // Sensor setup
  Serial.begin(115200);
  
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  qtr.setEmitterPin(2);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  // Enable motor driver

  pinMode(START_STOP_BUTTON, INPUT_PULLUP);  // Start/Stop button
  pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);   // Calibration button
  pinMode(STATUS_LED, OUTPUT);  // Status LED

  // WiFi verbinding
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
  Serial.print("IP-adres: ");
  Serial.println(WiFi.localIP());

  // Webserver routes
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);
  server.on("/start", handleStart);
  server.on("/calibrate", handleCalibrate);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();

  // Check physical buttons
  if (digitalRead(START_STOP_BUTTON) == LOW) {
    delay(50);  // Debounce
    if (digitalRead(START_STOP_BUTTON) == LOW) {
      isRunning = !isRunning;
      while (digitalRead(START_STOP_BUTTON) == LOW) {
        delay(10);  // Wait until button is released
      }
    }
  }

  if (digitalRead(CALIBRATE_BUTTON) == LOW) {
    delay(50);  // Debounce
    if (digitalRead(CALIBRATE_BUTTON) == LOW) {
      calibrateSensors();
      while (digitalRead(CALIBRATE_BUTTON) == LOW) {
        delay(10);  // Wait until button is released
      }
    }
  }

  if (isRunning) {
    uint16_t position = qtr.readLineBlack(sensorValues);
    float error = position - 3500;
    integral += error;
    float derivative = error - lastError;
    float output = Kp * error + Ki * integral + Kd * derivative;
    lastError = error;

    int leftSpeed = baseSpeed + output;
    int rightSpeed = baseSpeed - output;

    // Controleer of een wiel achteruit moet draaien
    if (leftSpeed < 0) {
      leftSpeed *= reverseFactor;  // Toepassen van reverseFactor
    }
    if (rightSpeed < 0) {
      rightSpeed *= reverseFactor;  // Toepassen van reverseFactor
    }

    // Snelheden beperken
    leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
    rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

    setMotor(leftSpeed, rightSpeed);

    // LED knipperen tijdens run
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= 500) {
      ledState = !ledState;
      digitalWrite(STATUS_LED, ledState);
      lastBlinkTime = currentTime;
    }
  } else {
    setMotor(0, 0);  // Stop motors
    digitalWrite(STATUS_LED, LOW);  // LED uit als niet aan het runnen
  }

  delay(10);
}

void setMotor(int leftSpeed, int rightSpeed) {
  if (leftSpeed > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, leftSpeed);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, -leftSpeed);
  }

  if (rightSpeed > 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, rightSpeed);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, -rightSpeed);
  }
}

void calibrateSensors() {
  Serial.println("Calibrating...");
  digitalWrite(STATUS_LED, HIGH);  // LED continu aan tijdens kalibratie
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
    delay(10);
  }
  digitalWrite(STATUS_LED, LOW);  // LED uit na kalibratie
  Serial.println("Calibration done!");
}

void handleRoot() {
  server.send(200, "text/html", 
    "<html>"
    "<body>"
    "<h1>PID Control Panel</h1>"
    "<form action='/update'>"
    "Kp: <input type='text' name='Kp' value='" + String(Kp) + "'><br>"
    "Ki: <input type='text' name='Ki' value='" + String(Ki) + "'><br>"
    "Kd: <input type='text' name='Kd' value='" + String(Kd) + "'><br>"
    "Base Speed: <input type='text' name='baseSpeed' value='" + String(baseSpeed) + "'><br>"
    "Max Speed: <input type='text' name='maxSpeed' value='" + String(maxSpeed) + "'><br>"
    "Reverse Factor: <input type='text' name='reverseFactor' value='" + String(reverseFactor) + "'><br>"
    "<input type='submit' value='Update'>"
    "</form>"
    "<a href='/start'>Start/Stop</a><br>"
    "<a href='/calibrate'>Calibrate</a>"
    "</body></html>");
}

void handleUpdate() {
  if (server.hasArg("Kp")) Kp = server.arg("Kp").toFloat();
  if (server.hasArg("Ki")) Ki = server.arg("Ki").toFloat();
  if (server.hasArg("Kd")) Kd = server.arg("Kd").toFloat();
  if (server.hasArg("baseSpeed")) baseSpeed = server.arg("baseSpeed").toInt();
  if (server.hasArg("maxSpeed")) maxSpeed = server.arg("maxSpeed").toInt();
  if (server.hasArg("reverseFactor")) reverseFactor = server.arg("reverseFactor").toFloat();
  server.send(200, "text/html", "Parameters updated! <a href='/'>Back</a>");
}

void handleStart() {
  isRunning = !isRunning;
  server.send(200, "text/html", String(isRunning ? "Started" : "Stopped") + " <a href='/'>Back</a>");
}

void handleCalibrate() {
  calibrateSensors();
  server.send(200, "text/html", "Calibration done! <a href='/'>Back</a>");
}
