#include <SparkFun_TB6612.h>

#include <SparkFun_TB6612.h>

//motor A
int pwmA = 3;
int in1A = 6;
int in2A = 5;

//motor B
int pwmB = 4;
int in1B = 7;
int in2B = 8;


int motorSpeed1 = 0;
int motorSpeed2 = 0;



void setup() {
  // put your setup code here, to run once:

  pinMode(pwmA,OUTPUT);
  pinMode(in1A,OUTPUT);
  pinMode(in2A,OUTPUT);
  pinMode(pwmB,OUTPUT);
  pinMode(in1B,OUTPUT);
  pinMode(in2B,OUTPUT);

  Serial.begin(9600);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(in1A,LOW);
  digitalWrite(in2A,HIGH);

  analogWrite(pwmA,motorSpeed1);

  if (motorSpeed1 < 230)
  {
    motorSpeed1 = motorSpeed1 +20;
    Serial.println(motorSpeed1);
    
  }

  delay(2000);
}
