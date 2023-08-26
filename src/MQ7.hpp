#ifndef MQ7_HPP
#define MQ7_HPP

#include <Arduino.h>
#include "MQ7.h"

#define MQ7_PIN A0
#define MQ7_BLYNK_VPIN_CO V3

extern float CO_PPM;



void readAndSendMQ7Data(void); 
void sendMQ7Data(void);

#endif // !MQ7_HPP