#include "ussensor.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "commonfunctions.h"

USSensor::USSensor(usSensor_t num, double angle) : Sensor(angle)
{
    this->num = num;
}

USSensor::~USSensor() {
    printf("Destroying us sensor %d\n", this->num);
}

void USSensor::updateValue(double curAngle, Point currentPosition, Map *map) {
    double sensorAngle = fmod(curAngle + this->angle + 2*PI, 2*PI);
    Line sensorLine = getSensorLine(currentPosition, sensorAngle);
    double distance = INFINITY;

    for (std::vector<LineSegment>::iterator it = map->lines.begin();
         it != map->lines.end(); ++it) {
        LineSegment segment = *it;
        distance = checkSegment(segment, sensorLine, sensorAngle, currentPosition, distance);
    }
    LineSegment bombSegments[4];
    map->bomb.getLineSegments(bombSegments);
    for (int i = 0; i < 4; i++) {
        LineSegment segment = bombSegments[i];
        distance = checkSegment(segment, sensorLine, sensorAngle, currentPosition, distance);
    }

    //printf("Sensor %d updated to value %f\n", this->num, distance);
    this->value = distance;
}


