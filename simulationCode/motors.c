#include <stdlib.h>                                                              
#include <stdio.h>                                                               
#include <unistd.h>                                                              
#include <fcntl.h>       

#include "motors.h"

static int motor_l;
static int motor_r;

void initMotors() {
	motor_l = 0;
	motor_r = 0;
	motor_l = open("/tmp/MotorL.pipe", O_WRONLY);
	if (motor_l < 0) {
		printf("Could not open left motor, error code %d\n", motor_l);
		return;
	}
	motor_r = open("/tmp/MotorR.pipe", O_WRONLY);
	if (motor_r < 0) {
		printf("Could not open right motor, error code %d\n", motor_r);
		return;
	}
	printf("Opened both motor files, ready to go on the motors\n");
}

void closeMotors() {
	close(motor_l);
	close(motor_r);
}

void setMotorSpeed(motor_t motor, int speed) {
	int fp = motor_l;
	switch(motor) {
		case MOTOR_LEFT:
			fp = motor_l;
			break;
		case MOTOR_RIGHT:
			fp = motor_r;
			break;
		default:
			printf("Invalid motor specified, chosen %d\n", motor);
			return;
	}

	if(fp < 0) {
		return;
	}
	int a = write(fp, &speed, sizeof(int));
	if(a != sizeof(int)) {
		printf("Could not write the speed for motor %d, error: %d\n", motor, a);
	}
}

void goForward() {
	setMotorSpeed(MOTOR_LEFT, MOTOR_SPEED_MAX);
	setMotorSpeed(MOTOR_RIGHT, MOTOR_SPEED_MAX);
}

void goReverse() {
	setMotorSpeed(MOTOR_LEFT, MOTOR_SPEED_MIN);
	setMotorSpeed(MOTOR_RIGHT, MOTOR_SPEED_MIN);
}

void turnLeft() {
	setMotorSpeed(MOTOR_LEFT, MOTOR_SPEED_MIN);
	setMotorSpeed(MOTOR_RIGHT, MOTOR_SPEED_MAX);
}

void turnRight() {
	setMotorSpeed(MOTOR_LEFT, MOTOR_SPEED_MAX);
	setMotorSpeed(MOTOR_RIGHT, MOTOR_SPEED_MIN);
}

void goFwdLeft() {
	setMotorSpeed(MOTOR_LEFT, 5);
	setMotorSpeed(MOTOR_RIGHT, MOTOR_SPEED_MAX);
}

void goFwdRight() {
	setMotorSpeed(MOTOR_LEFT, MOTOR_SPEED_MAX);
	setMotorSpeed(MOTOR_RIGHT, 5);
}

void stop() {
	setMotorSpeed(MOTOR_LEFT, 0);
	setMotorSpeed(MOTOR_RIGHT, 0);
}

void stopMotors() {
	setMotorSpeed(MOTOR_LEFT, 0);
	setMotorSpeed(MOTOR_RIGHT, 0);
}
