#include "MQ7.hpp"


MQ7 mq7(34, 3.3);
float CO_PPM = 0.0;
  
 
void readAndSendMQ7Data() 
{
  CO_PPM = mq7.getPPM();
  Serial.printf("CO: %f ppm\n", CO_PPM);

  sendMQ7Data();
}