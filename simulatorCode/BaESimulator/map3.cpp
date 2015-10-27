#include "map3.h"

#include <qglobal.h>
#include <QTime>

// S shape
Map3::Map3(double width, double height) : Map(width, height)
{

    this->addLineSegment(LineSegment(0.2*width, 0.6*height, 0.7*width, 0.6*height));
    this->addLineSegment(LineSegment(0.3*width, 0.4*height, 0.6*width, 0.4*height));
    this->addLineSegment(LineSegment(0.2*width, 0.8*height, 0.2*width, 0.2*height));
    this->addLineSegment(LineSegment(0.3*width, 0.4*height, 0.3*width, 0.2*height));
    this->addLineSegment(LineSegment(0.7*width, 0.8*height, 0.7*width, 0.2*height));
    this->addLineSegment(LineSegment(0.6*width, 0.4*height, 0.6*width, 0.2*height));
}
