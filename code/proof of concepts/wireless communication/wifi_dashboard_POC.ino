#include <WiFi.h>
#include <WebServer.h>

// Vervang deze waarden door je eigen netwerknaam en wachtwoord
const char* ssid = "googlewifi"; 
const char* password = "@fedex51"; 

WebServer server(80); // Maak een webserver op poort 80

// HTML-pagina voor het dashboard
const char* html = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>ESP32 Dashboard</title>
</head>
<body>
  <h1>ESP32 Dashboard</h1>
  <button onclick="location.href='/LED_ON'">LED AAN</button>
  <button onclick="location.href='/LED_OFF'">LED UIT</button>
</body>
</html>
)rawliteral";

// Pin voor de LED, vervang het door de pin die je wilt gebruiken
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); // Stel de LED-pin in als uitgang

  // Verbind met Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Bezig met verbinden...");
  }

  Serial.println("Verbonden met Wi-Fi!");
  Serial.print("IP-adres: ");
  Serial.println(WiFi.localIP());

  // Configuratie van de webserver
  server.on("/", handleRoot); // Root URL
  server.on("/LED_ON", handleLEDOn); // URL voor LED AAN
  server.on("/LED_OFF", handleLEDOff); // URL voor LED UIT
  server.begin(); // Start de webserver
}

void loop() {
  server.handleClient(); // Verwerk inkomende clientverzoeken
}

// Functie om de HTML-pagina te serveren
void handleRoot() {
  server.send(200, "text/html", html);
}

// Functie om de LED aan te zetten
void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", "<h1>LED AAN</h1><a href='/'>Terug</a>");
}

// Functie om de LED uit te zetten
void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", "<h1>LED UIT</h1><a href='/'>Terug</a>");
}
