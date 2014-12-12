#ifndef IRSENSOR_H
#define IRSENSOR_H

typedef enum {
	IRSENSOR_0 = 0,
	IRSENSOR_1,
	IRSENSOR_2,
	IRSENSOR_3,
	IRSENSOR_4,
	IRSENSOR_5,
	NUMBER_OF_IRSENSORS
} irsensor_t;

void initIRSensors();
void closeIRSensors();

int getIRSensor(irsensor_t);

#endif
