#include "ussensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>                                                              
#include <fcntl.h>       

int us_running = 0;
pthread_t us_thread[NUMBER_OF_USSENSORS];

typedef struct usdata {
	int number;
} usdata_t;

char *us_files[NUMBER_OF_USSENSORS] = {
	"USSensor0.pipe",
	"USSensor1.pipe",
	"USSensor2.pipe"
};

int usvalues[NUMBER_OF_USSENSORS];

usdata_t usData[NUMBER_OF_USSENSORS];

void *usThreadFunction(usdata_t *data){
	printf("US Sensor thread %d started\n", data->number);
	int num = data->number;
	int file = open(us_files[num], O_RDONLY);
	if (file < 0) {
		printf("Could not open US sensor %d, error code %d\n", num, file);
		return NULL;
	}
	while(us_running) {
		int prev = usvalues[num];
		int new;
		read(file, &new, 4);
		if(prev != new) {
			usvalues[num] = new;
			printf("Got new value for US sensor %d: %d\n", num, usvalues[num]);
		}
	}
	close(file);
	return NULL;
}

void initUSSensors() {
	us_running = 1;
	for (int i = 0; i < NUMBER_OF_USSENSORS; i++) {
		usvalues[i] = 300;
		usData[i].number = i;
		pthread_create(&us_thread[i], NULL, (void *(*)(void*))usThreadFunction, &usData[i]); 
	}
}

void closeUSSensors() {
	us_running = 0;
}

int getUSSensor(ussensor_t sensor) {
	if (sensor >= USSENSOR_0 && sensor < NUMBER_OF_USSENSORS) {
		int i = usvalues[sensor];
		return i;
	} 
	return 300;
}
