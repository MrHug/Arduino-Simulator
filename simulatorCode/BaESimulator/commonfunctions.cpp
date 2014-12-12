#include "commonfunctions.h"

#include <math.h>
#include <stdio.h>
#include <cmath>

double normalizedAngle(double angle) {
    angle = fmod(angle + 2*PI, 2*PI);
    if (std::abs(angle - 2*PI) < EPSILON) {
        angle = 0;
    }
    return angle;
}

bool doubleEquals(double a, double b) {
    return std::abs(a-b) < EPSILON;
}

double dabs(double a) {
    return (a < 0) ? -a : a;
}
