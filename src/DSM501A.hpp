#ifndef DSM501A
#define DSM501A

extern int pin;
extern unsigned long duration;
extern unsigned long starttime;
extern unsigned long sampletime_ms;
extern unsigned long lowpulseoccupancy;
extern float ratio;
extern float concentration;

void DSM501A_SetUp(void);
void DSM501A_ReadData(void);

#endif // !DSM501A


