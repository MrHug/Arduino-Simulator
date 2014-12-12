#ifndef SENSOR_H
#define SENSOR_H

#include "point.h"
#include "map.h"

class Sensor {
public:
    Sensor(double angle) {this->angle = angle; this->value = 0;}
    virtual ~Sensor(){}
    virtual void updateValue(double curAngle, Point currentPosition, Map *map) {}

    int getValue() {return (int)(value + 0.5);}
    double getAngle() {return angle;}
    void setAngle(double a) {this->angle = a;}
protected:
    double angle;
    double value;

    double checkSegment(LineSegment segment, Line sensorLine, double sensorAngle, Point currentPosition, double prevDistance);
    Line getSensorLine(Point currentPosition, double sensorAngle);
};

#endif // SENSOR_H
