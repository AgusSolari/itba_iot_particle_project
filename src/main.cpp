
// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates

#include "DHT.hpp"
#include "MQ7.hpp"
#include "DSM501A.hpp"

// Add the required libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h> // You need to add it by searching "Adafruit unified sensor" in libraries and inslall it
#include <HTTPClient.h>
#include <ctime>
#include <ESP32Ping.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Enter your WIFI SSID and password
// char ssid[] = "Personal-B57-2.4GHz";
// char pass[] = "0112310B57";
char ssid[] = "iPhone de Agustin";
char pass[] = "agus44131529";
char auth[] = "YNUbAxphbRpRGYf4ZA2QDT7CEADaoXC1";

int RUN = 0;

String GOOGLE_SCRIPT_LINK = "https://script.google.com/macros/s/AKfycbyyp8iwZTNuZZmJ8UMk0m0PcAcMl31Q5WoqeV94QLQIkdaGIGZtNHnijPOyrEs38rqb2A/exec?";
BlynkTimer timer;

// SETUP BLOCK

void sendData()
{
  Serial.println("Sending data");
  String domain = GOOGLE_SCRIPT_LINK + "temperature=" + String(TEMPERATURE) + "&humidity=" + String(HUMIDITY) + "&co_ppm=" + String(CO_PPM) + "&pcl_concentration=" + String(concentration);
  Serial.println(domain);

  HTTPClient http;
  http.begin(domain);
  int httpCode = http.GET();

  if (httpCode > 0)
  {
    Serial.println("Data sent SUCCESSFULLY");
  }
  else
  {
    Serial.println("Data sent FAILED");
  }

  http.end();
}

void lcdUpdate()
{
  lcd.setCursor(0,0);
  lcd.print("Temp: " + String(TEMPERATURE) + " C");
  lcd.setCursor(0,1);
  lcd.print("Hum: " + String(HUMIDITY) + " %");
   lcd.setCursor(0,2);
  lcd.print("CO: " + String(CO_PPM) + " ppm");
   lcd.setCursor(0,3);
  lcd.print("Pcs: " + String(concentration) + " pcs/m3");
}

void readAndSendSensorsData()
{
  readAndSendDHTData();
  readAndSendMQ7Data();
  DSM501A_ReadData();

  lcdUpdate();

  sendData();
}

void sendDHTData()
{
  Serial.println("Sending DHT data");
  Blynk.virtualWrite(DHT_BLYNK_VPIN_TEMPERATURE, TEMPERATURE);
  Blynk.virtualWrite(DHT_BLYNK_VPIN_HUMIDITY, HUMIDITY);
}
void sendMQ7Data()
{
  Serial.println("Sending MQ7 data");
  Blynk.virtualWrite(MQ7_BLYNK_VPIN_CO, CO_PPM);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  WiFi.begin(ssid, pass);

  setupDHT();
  DSM501A_SetUp();

  // Set up timer to run every 5 sec
  timer.setInterval(5000L, readAndSendSensorsData);

  lcd.init();
  lcd.backlight();

}

void loop()
{
  Blynk.run();
  timer.run();
}
