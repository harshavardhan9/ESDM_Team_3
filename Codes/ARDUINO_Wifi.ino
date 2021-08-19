#include "LowPower.h"
int Trig = 8, Echo = 9;
float t, D, bat = 3.3;
int PckNm = 1, Node = 1;
String MainString = "";

void setup()
{
  Serial.begin(9600);
  pinMode(Trig , OUTPUT);
  pinMode(Echo , INPUT);
}

void loop()
{
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  digitalWrite(Trig , HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig , LOW);
  t = pulseIn(Echo , HIGH);
  D=t/58.138; 
  MainString = "$#@Distance:" + String(D) + "  Node:1  Bat volt:3.3v  Packet No.:" +String(PckNm)+"#";
//  MainString = "*" + String(D) + "$" +String(PckNm)+ "#";
  Serial.println(MainString);
  delay(500);
  PckNm += 1;  
}
