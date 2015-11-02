#ifndef MOTORS_H
#define MOTORS_H

typedef enum {
	MOTOR_LEFT = 0,
	MOTOR_RIGHT,
	NUMBER_OF_MOTORS
} motor_t;

#define MOTOR_SPEED_MAX 10
#define MOTOR_SPEED_MIN -10

void initMotors();
void closeMotors();

void goForward();
void goReverse();
void turnLeft();
void turnRight();
void goFwdLeft();
void goFwdRight();
void stop();
void stopMotors();

#endif
