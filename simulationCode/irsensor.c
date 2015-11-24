#include "irsensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>                                                              
#include <fcntl.h>       

int ir_running = 0;
pthread_t ir_thread[NUMBER_OF_IRSENSORS];

typedef struct irdata {
	int number;
} irdata_t;

char *ir_files[NUMBER_OF_IRSENSORS] = {
	"/tmp/IRSensor0.pipe",
	"/tmp/IRSensor1.pipe",
	"/tmp/IRSensor2.pipe",
	"/tmp/IRSensor3.pipe",
	"/tmp/IRSensor4.pipe",
	"/tmp/IRSensor5.pipe"
};

int irvalues[NUMBER_OF_IRSENSORS];

irdata_t irData[NUMBER_OF_IRSENSORS];

void *irThreadFunction(irdata_t *data){
	printf("IR Sensor thread %d started\n", data->number);
	int num = data->number;
	int file = open(ir_files[num], O_RDONLY);
	if (file < 0) {
		printf("Could not open IR sensor %d, error code %d\n", num, file);
		return NULL;
	}
	while(ir_running) {	
		int prev =irvalues[num];
		int new;
		read(file, &new, 4);
		if (new != prev) {
			irvalues[num] = new;
			printf("Read new value %d for IR sensor %d\n", new, num);
		}
	}
	close(file);
	return NULL;
}

void initIRSensors() {
	ir_running = 1;
	for (int i = 0; i < NUMBER_OF_IRSENSORS; i++) {
		irData[i].number = i;
		pthread_create(&ir_thread[i], NULL, (void *(*)(void*))irThreadFunction, &irData[i]); 
	}
}

void closeIRSensors() {
	ir_running = 0;
}

int getIRSensor(irsensor_t sensor) {
	if (sensor >= IRSENSOR_0 && sensor < NUMBER_OF_IRSENSORS) {
		return irvalues[sensor];
	} 
	return 0;
}
