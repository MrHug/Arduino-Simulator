#include "sensor.h"

#include <math.h>
#include <stdio.h>

#include "commonfunctions.h"

double Sensor::checkSegment(LineSegment segment, Line sensorLine, double sensorAngle, Point currentPosition, double prevDistance) {
    double distance = prevDistance;
    if (segment.isIntersect(sensorLine)) {
        Point intersection = segment.getIntersect(sensorLine);
        //intersection.print();

        double pointAngle = atan2(intersection.y-currentPosition.y, intersection.x-currentPosition.x);
        pointAngle = normalizedAngle(0.5*PI-pointAngle);
        //printf("pointAngle %f, sensorAngle %f\n", pointAngle, sensorAngle);

        if (dabs(pointAngle - sensorAngle) < EPSILON) {
            //printf("Angles match\n");
            LineSegment sensorWallLine(currentPosition, intersection);
            if (sensorWallLine.length() < distance) {
                distance = sensorWallLine.length();
            }
        }
    }
    return distance;
}

Line Sensor::getSensorLine(Point currentPosition, double sensorAngle) {
    Point otherPoint(currentPosition.x + sin(sensorAngle), currentPosition.y + cos(sensorAngle));
    return Line(currentPosition, otherPoint);
}
