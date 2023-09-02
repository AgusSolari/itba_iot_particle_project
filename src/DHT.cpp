// DHT_DATA.cpp

#include "DHT.hpp"


float HUMIDITY = 0.0; // Puedes inicializar estas variables según tus necesidades
float TEMPERATURE = 0.0;
DHT dht(DHTPIN, DHTTYPE);

// Definición de las variables globales
int DHT_ENABLED = 0;
float HUMIDITY_IGNORED_DELTA = 0.01;
float TEMPERATURE_IGNORED_DELTA = 0.01;

//DHT setup
void setupDHT() {
  Serial.println("DHT startup!");
  dht.begin();
  DHT_ENABLED = 1;
}

//Reading DHT data
void readAndSendDHTData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT");
  } else {
    float humidityDelta = abs(humidity - HUMIDITY) - HUMIDITY_IGNORED_DELTA;
    float temperatureDelta = abs(temperature - TEMPERATURE) - HUMIDITY_IGNORED_DELTA;
    if (humidityDelta > 0 || temperatureDelta > 0) {
      HUMIDITY = humidity;
      TEMPERATURE = temperature;
      Serial.printf("Humidity: %f%%. Temperature: %f*C.\n", humidity, temperature);  
      sendDHTData();
    }
  }
}

