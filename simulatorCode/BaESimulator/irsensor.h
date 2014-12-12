#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "sensor.h"
#include "commonfunctions.h"

#define MAX_SIGNAL_VALUE    100.0
#define MAX_SIGNAL_DISTANCE 600.0
#define MAX_SIGNAL_ANGLE    0.5*PI
#define SIGNAL_EXPONENTIAL_DECAY 0.26611849461 // Based on 0 deg = 100%, 30 deg = 50%.
#define RANDOM_JITTER 5

typedef enum {
    IR_SENSOR_0 = 0,
    IR_SENSOR_1,
    IR_SENSOR_2,
    IR_SENSOR_3,
    IR_SENSOR_4,
    IR_SENSOR_5,
    NUMBER_OF_IR_SENSORS
} irSensor_t;

class IRSensor : public Sensor
{
public:
    IRSensor(irSensor_t num, double angle = 0);
    void updateValue(double curAngle, Point currentPosition, Map *map);

    irSensor_t num;

private:
    double calculateValue(double distance, double angleDisplacement);
};

#endif // IRSENSOR_H
