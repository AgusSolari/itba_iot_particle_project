// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "DSM501A.hpp"


int pin = 16;
unsigned long duration = 0;
unsigned long starttime = 0;
unsigned long sampletime_ms = 5000;
unsigned long lowpulseoccupancy = 0;
unsigned long endtime = 0;
float ratio = 0;
float concentration = 0;



void DSM501A_SetUp() {
  pinMode(pin,INPUT);
  delay(2000);
  starttime = millis();//get the current time;

}

void DSM501A_ReadData() {

  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis()-starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancy/((millis()-starttime)*10.0);
    concentration = 15006/24.32*ratio/283*1e6; //pcl / m3
    lowpulseoccupancy = 0;

    Serial.printf("Concentration = %f pcs/m3 \n", concentration);
  }

}