#include "map4.h"

#include <qglobal.h>
#include <QTime>

// Single wall ahead
Map4::Map4(double width, double height) : Map(width, height)
{

    this->addLineSegment(LineSegment(0.0*width, 0.7*height, 1.0*width, 0.7*height));
}
