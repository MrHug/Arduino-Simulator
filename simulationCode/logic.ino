#include "motors.h"
#include "ussensor.h"
#include "irsensor.h"

#define STATE_FORWARD   0
#define STATE_RIGHT     1
#define STATE_LEFT      2
#define STATE_FWD_RIGHT 3
#define STATE_FWD_LEFT  4
#define STATE_STOP      5

#define LEFT_US USSENSOR_0
#define FRONT_US USSENSOR_1
#define RIGHT_US USSENSOR_2

#define MIN_DISTANCE_RIGHT 20
#define MAX_DISTANCE_RIGHT 40
#define MIN_DISTANCE_FRONT 40
#define MAX_DISTANCE_FRONT 90

int state = STATE_FORWARD;

irsensor_t getHighestIRSensorIndex() {
	irsensor_t index = NUMBER_OF_IRSENSORS;
	int max = -1;
	for (int i = IRSENSOR_0; i< NUMBER_OF_IRSENSORS; i++) {
		int sensValue = getIRSensor(i);
		if (sensValue > max) {
			index = i;
			max = sensValue;
		}
	}
	Serial.println(index);
	pinMode(13, HIGH);
	return index;
}

void setup() { // put your setup code here, to run once: initMotors();
	initUSSensors();
	initIRSensors();
	initMotors();
	turnLeft();
}

void loop() {
	// put your main code here, to run repeatedly:
	switch(state) {
		case STATE_FORWARD:
			goForward();
			if (getUSSensor(FRONT_US) < MIN_DISTANCE_FRONT) {
				state = STATE_LEFT;
			} else if (getUSSensor(RIGHT_US) > MAX_DISTANCE_RIGHT) {
				state = STATE_FWD_RIGHT;
			} else if (getUSSensor(RIGHT_US) < MIN_DISTANCE_RIGHT) {
				state = STATE_FWD_LEFT;
			}
			break;
		case STATE_RIGHT:
			turnRight();
			break;
		case STATE_LEFT:
			turnLeft();
			if (getUSSensor(FRONT_US) > MAX_DISTANCE_FRONT) {
				state = STATE_FORWARD;
			}
			break;
		case STATE_FWD_RIGHT:
			goFwdRight();
			if (getUSSensor(RIGHT_US) < MAX_DISTANCE_RIGHT) {
				state = STATE_FORWARD;
			}
			break;
		case STATE_FWD_LEFT:
			goFwdLeft();
			if (getUSSensor(RIGHT_US) > MAX_DISTANCE_RIGHT) {
				state = STATE_FORWARD;
			}
			break;
		case STATE_STOP:
			stop();
			break;
	}
}


