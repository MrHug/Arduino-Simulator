#ifndef USSENSOR_H
#define USSENSOR_H

typedef enum {
	USSENSOR_0 = 0,
	USSENSOR_1,
	USSENSOR_2,
	NUMBER_OF_USSENSORS
} ussensor_t;

void initUSSensors();
void closeUSSensors();

void updateUSSensors();
int getUSSensor(ussensor_t);

#endif
