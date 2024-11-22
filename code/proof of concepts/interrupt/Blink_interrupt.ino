#include <Arduino.h>

int button = 7;
volatile bool stopPressed = false;
unsigned long vorige;
int LEDpin = 15;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT_PULLUP);
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin,HIGH);
  

  attachInterrupt(digitalPinToInterrupt(button), stopProgram, FALLING);
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    if (stopPressed)
    {
      Serial.println("pressed");
      digitalWrite(LEDpin,LOW);
      delay(5000);
      stopPressed = false;
    }
    else 
    { 
      if (millis()- vorige > 500)
      {
            vorige = millis();

            bool LED = digitalRead(LEDpin);
            if (LED == HIGH)
        {
            digitalWrite (LEDpin,LOW);
        }
       else if (LED == LOW)
        {
            digitalWrite(LEDpin,HIGH);
        } 
       }
       
    }

}

void stopProgram() 
{
  stopPressed = true;
}
