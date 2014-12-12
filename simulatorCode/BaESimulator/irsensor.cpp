#include "irsensor.h"

#include "math.h"
#include <qglobal.h>
#include <QTime>

IRSensor::IRSensor(irSensor_t num, double angle) : Sensor(angle)
{
    this->num = num;
    qsrand(QTime::currentTime().msec());
}

void IRSensor::updateValue(double curAngle, Point currentPosition, Map *map) {
    double sensorAngle = fmod(curAngle + this->angle + 2*PI, 2*PI);
    Point bombPosition = map->bomb.getPoint();
    LineSegment robotBombLine = LineSegment(currentPosition, bombPosition);
    double lineDistance = INFINITY;
    double newValue = 0;

    for (std::vector<LineSegment>::iterator it = map->lines.begin();
         it != map->lines.end(); ++it) {
        LineSegment segment = *it;
        lineDistance = checkSegment(segment, robotBombLine, sensorAngle, currentPosition, lineDistance);
    }

    double bombDistance = robotBombLine.length();

    if (bombDistance < lineDistance) {
        double bombAngle = atan2(bombPosition.y-currentPosition.y, bombPosition.x-currentPosition.x);
        bombAngle = normalizedAngle(0.5*PI - bombAngle);
        double displacement = fmod(dabs(bombAngle-sensorAngle), PI + 0.01);
        newValue = calculateValue(bombDistance, displacement);
    }

    //printf("IR Sensor %d updated to value %f\n", this->num, newValue);
    this->value = newValue;
}

double IRSensor::calculateValue(double distance, double angleDisplacement) {
    double result = 0;

    // First scale linearly for distance:
    result = -(MAX_SIGNAL_VALUE/MAX_SIGNAL_DISTANCE) * distance + MAX_SIGNAL_VALUE;

    // Now scale exponentially for angle:
    result *= pow(SIGNAL_EXPONENTIAL_DECAY, angleDisplacement);

    if (result < 0) {
        return 0;
    }

    return result + qrand() % RANDOM_JITTER;
}
