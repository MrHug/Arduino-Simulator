#ifndef ROBOT_H
#define ROBOT_H

#include "motor.h"
#include "ussensor.h"
#include "irsensor.h"
#include "line.h"
#include "map.h"

#define ROBOT_WIDTH     10
#define ROBOT_HEIGHT    10
#define SPEED_FACTOR    0.25

class Robot
{
public:
    Robot();
    ~Robot();

    void move();
    void updateSensors(Point center, Map *map);
    Point *getPoints();
    Point getCenter();

    Motor leftMotor;
    Motor rightMotor;
    USSensor *usSensors[NUMBER_OF_US_SENSORS];
    IRSensor *irSensors[NUMBER_OF_IR_SENSORS];

private:
    Point p[4];

    void rotateAndTranslatePoints(double angle, Point *translation);
    void resetPoints();


    double getAngle(Point leftCenter, Point rightCenter);
    Line getLineThroughBothMotors();
    Line getLineForMotor(Motor motor);

    Point getLeftCenter();
    Point getRightCenter();


    double getSpeed(Motor motor);
};

#endif // ROBOT_H
