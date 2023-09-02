
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

int WIFI_ON = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Enter your WIFI SSID and password
// char ssid[] = "Personal-B57-2.4GHz";
// char pass[] = "0112310B57";
char ssid1[] = "iPhone de Victoria";
char pass1[] = "1234567890";
char ssid2[] = "Lu";
char pass2[] = "12345678";
char auth[] = "YNUbAxphbRpRGYf4ZA2QDT7CEADaoXC1";

char *ssid;
char *pass;

int RUN = 0;

String GOOGLE_SCRIPT_LINK = "https://script.google.com/macros/s/AKfycbyyp8iwZTNuZZmJ8UMk0m0PcAcMl31Q5WoqeV94QLQIkdaGIGZtNHnijPOyrEs38rqb2A/exec?";
BlynkTimer timer;

// SETUP BLOCK

void sendData()
{
  Serial.println("Sending data");
  String domain = GOOGLE_SCRIPT_LINK + "temperature=" + String(TEMPERATURE) + "&humidity=" + String(HUMIDITY) + "&co_ppm=" + String(CO_PPM) + "&pcl_concentration=" + String(concentration);
  // Serial.println(domain);

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
  lcd.clear();
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

  if(WIFI_ON == true)
  {
    sendData();
    Serial.println("Blynk.run");
  }

}

void sendDHTData()
{
  // Serial.println("Sending DHT data");
  Blynk.virtualWrite(DHT_BLYNK_VPIN_TEMPERATURE, TEMPERATURE);
  Blynk.virtualWrite(DHT_BLYNK_VPIN_HUMIDITY, HUMIDITY);
}
void sendMQ7Data()
{
  // Serial.println("Sending MQ7 data");
  Blynk.virtualWrite(MQ7_BLYNK_VPIN_CO, CO_PPM);
}

void sendDSM501AData()
{
  Blynk.virtualWrite(DSM_BLYNK_VPIN_CO, concentration);
}

void checkWiFi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi disconnected");
    WIFI_ON = false;
  }
  else
  {
    Serial.println("WiFi connected");
    WIFI_ON = true;
  }
}

void lcdShowWelcome(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("Air Quality");
  lcd.setCursor(0,2);
  lcd.print("Monitoring");
  lcd.setCursor(0,3);
  lcd.print("System");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print("WiFi");
  lcd.setCursor(0,2);
  lcd.print("Please wait...");
  lcd.setCursor(0,3);
  lcd.print(" ");
  delay(2000);
  
  if(WIFI_ON == true)
  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("WiFi: " + String(ssid));
    delay(2000);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("No connection to WiFi");
    delay(2000);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid1, pass1);
  delay(1000);
  checkWiFi();

  if(WIFI_ON == true)
  {
    ssid = ssid1;
    pass = pass1;
  }
  else
  {
    WiFi.begin(ssid2, pass2);
    delay(1000);
    checkWiFi();

    if(WIFI_ON == true)
    {
      ssid = ssid2;
      pass = pass2;
    }
  }

  

  setupDHT();
  DSM501A_SetUp();
  lcd.init();
  lcd.backlight();
  lcdShowWelcome();

  if(WIFI_ON == true)
  {
    Serial.println("Blynk.begin");
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    timer.setInterval(5000L, readAndSendSensorsData);  // Set up timer to run every 5 sec
  }

}

void loop()
{
  if(WIFI_ON == true)
  {
    Blynk.run();
    timer.run();
  }
  else
  {
    readAndSendSensorsData();
    Serial.println("NOWIFI");
    delay(5000);
  }
}
