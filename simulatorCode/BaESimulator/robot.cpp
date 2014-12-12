#include "robot.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "commonfunctions.h"

Robot::Robot() : leftMotor(MOTOR_LEFT), rightMotor(MOTOR_RIGHT)
{
    resetPoints();
    for (int i = US_SENSOR_0; i < NUMBER_OF_US_SENSORS; i++) {
        usSensors[i] = new USSensor((usSensor_t) i, normalizedAngle(/*-0.5*PI + */i*0.5*PI));
    }
    for (int i = IR_SENSOR_0; i < NUMBER_OF_IR_SENSORS; i++) {
        irSensors[i] = new IRSensor((irSensor_t) i, normalizedAngle(/*-2.0/3*PI +*/ i*1.0/3*PI));
    }
}

Robot::~Robot() {
    for (int i = US_SENSOR_0; i < NUMBER_OF_US_SENSORS; i++) {
        delete usSensors[i];
    }
    for (int i = IR_SENSOR_0; i < NUMBER_OF_IR_SENSORS; i++) {
        delete irSensors[i];
    }
}

void Robot::move() {
    Point leftCenter = getLeftCenter();
    Point rightCenter = getRightCenter();

//    Line leftLine = getLineForMotor(leftMotor);
//    Line rightLine = getLineForMotor(rightMotor);
    double angle = getAngle(leftCenter, rightCenter);

    /*printf("Before: \n");
    leftCenter.print();
    rightCenter.print();
    printf("Angle %f\n", angle *180/PI);*/


    // First determine where the motors end up.
    leftCenter.x = leftCenter.x + getSpeed(leftMotor)*sin(angle);
    leftCenter.y = leftCenter.y + getSpeed(leftMotor)*cos(angle);

    rightCenter.x = rightCenter.x + getSpeed(rightMotor)*sin(angle);
    rightCenter.y = rightCenter.y + getSpeed(rightMotor)*cos(angle);

    /*printf("After: \n");
    leftCenter.print();
    rightCenter.print();*/

    // Determine the angle the robot is now facing, needed for rotation of the point.
    double newAngle = getAngle(leftCenter, rightCenter);

    //printf("%f new angle\n\n", newAngle*180/PI);

    // Needed for translation of the points.
    Point newCenter;
    newCenter.x = (rightCenter.x - leftCenter.x)/2 + leftCenter.x;
    newCenter.y = (rightCenter.y - leftCenter.y)/2 + leftCenter.y;

    rotateAndTranslatePoints(newAngle, &newCenter);
}

void Robot::updateSensors(Point center, Map *map) {
    double angle = getAngle(getLeftCenter(), getRightCenter());
    for (int i = US_SENSOR_0; i< NUMBER_OF_US_SENSORS; i++) {
        usSensors[i]->updateValue(angle, center, map);
    }
    for (int i = IR_SENSOR_0; i < NUMBER_OF_IR_SENSORS; i++) {
        irSensors[i]->updateValue(angle, center, map);
    }
}

void Robot::rotateAndTranslatePoints(double angle, Point *translation) {
    resetPoints();
    for (int i = 0; i < 4; i++) {
        //Rotate (rotation matrix stuff)
        double x = p[i].x;
        double y = p[i].y;
        p[i].x = x*cos(angle) + y*sin(angle);
        p[i].y = -x*sin(angle) + y*cos(angle);
        //Translate
        p[i].x += translation->x;
        p[i].y += translation->y;
    }
}

void Robot::resetPoints() {
    for (int i = 0; i < 4; i++) {
        p[i].x = ((i == 0 || i == 3) ? -1 : 1) * ROBOT_WIDTH/2.0;
        p[i].y = ((i == 2 || i == 3) ? -1 : 1) * ROBOT_HEIGHT/2.0;
    }
}

Point *Robot::getPoints() {
    return p;
}

double Robot::getAngle(Point leftCenter, Point rightCenter) {
    Line centerLine(leftCenter, rightCenter);
    Line leftLine = centerLine.perpendicular(leftCenter);
    if (doubleEquals(leftLine.b,0)) {
        return (leftCenter.x < rightCenter.x) ? 0 : PI;
    }
    double angle = atan(-leftLine.a/leftLine.b);
    //printf("Angle is now %f\n", angle);
    if (leftCenter.x < rightCenter.x) {
        // Facing North
        if (leftCenter.y < rightCenter.y) {
            // Facing NorthWest
            return normalizedAngle(1.5*PI - angle);
        } else {
            // Facing NorthEast
            return normalizedAngle(0.5*PI - angle);
        }
    } else {
        // Facing South
        if (leftCenter.y < rightCenter.y) {
            // Facing SouthWest
            return normalizedAngle(1.5*PI-angle);
        } else {
            // Facing SouthEast
            return normalizedAngle(0.5*PI-angle);
        }
    }
}

Line Robot::getLineThroughBothMotors() {
    Point leftCenter = getLeftCenter();
    Point rightCenter = getRightCenter();
    return Line(leftCenter, rightCenter);
}

Line Robot::getLineForMotor(Motor motor) {
    Line motorLine = getLineThroughBothMotors();
    Point motorPoint;
    if (motor.type == MOTOR_LEFT) {
        motorPoint = getLeftCenter();
    } else {
        motorPoint = getRightCenter();
    }
    return motorLine.perpendicular(motorPoint);
}

Point Robot::getLeftCenter() {
    return Point(p[3].x + (p[0].x - p[3].x)/2,
                 p[3].y + (p[0].y - p[3].y)/2);
}

Point Robot::getRightCenter() {
    return Point(p[2].x + (p[1].x - p[2].x)/2,
                 p[2].y + (p[1].y - p[2].y)/2);
}

Point Robot::getCenter() {
    return Point(p[0].x + (p[1].x - p[0].x)/2, p[0].y + (p[3].y - p[0].y)/2);
}

double Robot::getSpeed(Motor motor) {
    return motor.speed * SPEED_FACTOR;
}

