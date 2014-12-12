#include "point.h"

#include <stdlib.h>
#include <stdio.h>

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Point::print() {
    printf("Point at (%f,%f)\n", x,y);
}
