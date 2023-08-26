// DHT_DATA.h

#ifndef DHT_DATA_H
#define DHT_DATA_H

#include <Arduino.h>
#include <DHT.h>



#define DHTPIN 4
#define DHTTYPE DHT22

//Blynk settings and configuration
#define BLYNK_TEMPLATE_ID "TMPL2mZ-bUWDb"
#define BLYNK_TEMPLATE_NAME "DHT22"
#define BLYNK_AUTH_TOKEN "YNUbAxphbRpRGYf4ZA2QDT7CEADaoXC1"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial


//DHT sensor settings and configuration
#define DHT_BLYNK_VPIN_TEMPERATURE V0 //Virtual pin on Blynk side
#define DHT_BLYNK_VPIN_HUMIDITY V1 //Virtual pin on Blynk side

// Declaración de las variables globales (en el archivo de cabecera)
extern int DHT_ENABLED;
extern float HUMIDITY_IGNORED_DELTA;
extern float TEMPERATURE_IGNORED_DELTA;

extern float HUMIDITY;
extern float TEMPERATURE;

void setupDHT(void);
void readAndSendDHTData(void);
void sendDHTData(void);







#endif // DHT_DATA_H