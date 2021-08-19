#include "LowPower.h"
#include <SPI.h> //Import SPI librarey 
#include <RH_RF95.h> // RF95 from RadioHead Librarey 

#define RFM95_CS 10 //CS if Lora connected to pin 10
#define RFM95_RST 9 //RST of Lora connected to pin 9
#define RFM95_INT 2 //INT of Lora connected to pin 2

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 434.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int Trig = 6, Echo = 7;
float t, D, bat = 3.3;
int PckNm = 1, Node = 1;
String MainString = "";

char value = 48;
char buff[55];

void setup()
{

  //Initialize Serial Monitor
  Serial.begin(9600);

  // Reset LoRa Module
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  //Initialize LoRa Module
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }


  //Set the default frequency 434.0MHz
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }

  rf95.setTxPower(18); //Transmission power of the Lora Module

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
  D = t / 58.138;
  MainString = "Distance:" + String(D) + "  Node:1  Bat volt:3.3v  Packet No.:" + String(PckNm);
  Serial.println(MainString);
  MainString.toCharArray(buff, MainString.length()+1);
  rf95.send((uint8_t *)buff, MainString.length()+1);
  Serial.println(buff);
  delay(1000);
  PckNm += 1;
  
}
