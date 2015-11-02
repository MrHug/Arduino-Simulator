#include "logic.h"
#include "sensors.h"

int switch0 = 12;
int switch1 = 13;

void setup() { // put your setup code here, to run once:
      initUSSensors();
      initIRSensors();
      initMotors();

      Serial.begin(9600);
      pinMode(13, OUTPUT);
      pinMode(switch0, INPUT);
      pinMode(switch1, INPUT);
}


void loop() {
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
 delay(500);
}

int getSwitchValue() {
  int a = digitalRead(switch0);
  int b = digitalRead(switch1);
  return 2*b + a;
}


int main() {
	setup();
	while(1) {
		loop();
		usleep(10000);
	}
	return 0;
}
