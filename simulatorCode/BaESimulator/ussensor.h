#ifndef USSENSOR_H
#define USSENSOR_H

#include "sensor.h"

typedef enum {
    US_SENSOR_0 = 0,
    US_SENSOR_1,
    US_SENSOR_2,
    NUMBER_OF_US_SENSORS
} usSensor_t;

class USSensor : public Sensor
{
public:
    USSensor(usSensor_t num, double angle = 0);
    ~USSensor();
    void updateValue(double curAngle, Point currentPosition, Map *map);

    usSensor_t num;
};



#endif // USSENSOR_H
