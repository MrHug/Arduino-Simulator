#include "map4.h"

#include <qglobal.h>
#include <QTime>

// Single wall ahead
Map4::Map4(double width, double height) : Map(width, height)
{

    this->addLineSegment(LineSegment(0.2*width, 0.7*height, 0.8*width, 0.7*height));
}
