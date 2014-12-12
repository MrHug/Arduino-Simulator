#ifndef MOTOR_H
#define MOTOR_H

#include "point.h"

typedef enum {
    MOTOR_LEFT,
    MOTOR_RIGHT
} motor_t;

class Motor
{
public:
    Motor(motor_t type);

    int speed;
    motor_t type;
private:
};

#endif // MOTOR_H
