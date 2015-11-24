#include "logic.h"
#include "sensors.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>                                                              
#include <fcntl.h>       

int switchvalue;
pthread_t switch_thread;

void *switchThreadFunction(){
	printf("Switch thread started\n");
	int file = open("taskSwitch.pipe", O_RDONLY);
	if (file < 0) {
		printf("Could not open Switch, error code %d\n", file);
		return NULL;
	}
	while(1) {
		int prev = switchvalue;
		int new;
		read(file, &new, 4);
		if(prev != new) {
			switchvalue = new;
			printf("Got new switch value: %d\n", new);
		}
	}
	close(file);
	return NULL;
}

void initSwitch() {
	pthread_create(&switch_thread, NULL, (void *(*)(void*))switchThreadFunction, NULL); 
}

void setup() { // put your setup code here, to run once:
      initUSSensors();
      initIRSensors();
      initMotors();
			initSwitch();
}

int getSwitchValue() {
  return switchvalue;
}

void loop() {
updateUSSensors();
 switch(getSwitchValue()) { 
   case 0:
     task1();
     break;
   case 1:
     task2();
     break;
   case 2:
     task3();
     break;
 }
}



int main() {
	setup();
	while(1) {
		loop();
		usleep(10000);
	}
	return 0;
}

int digitalRead(int a) {
	return 0;
}

int analogRead(int a) {
	return 0;
}
