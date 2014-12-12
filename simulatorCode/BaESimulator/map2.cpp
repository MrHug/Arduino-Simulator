#include "map2.h"

#include <qglobal.h>
#include <QTime>

// S shape
Map2::Map2(double width, double height) : Map(width, height)
{
    int h1 = height/7;
    int w1 = width/7;

    this->addLineSegment(LineSegment(w1,0,w1,h1));
    this->addLineSegment(LineSegment(0,2*h1,6*w1,2*h1));
    this->addLineSegment(LineSegment(w1,h1,width,h1));
    this->addLineSegment(LineSegment(6*w1,2*h1,6*w1,3*h1));
    this->addLineSegment(LineSegment(width,4*h1,w1,4*h1));
    this->addLineSegment(LineSegment(6*w1,3*h1,0,3*h1));
    this->addLineSegment(LineSegment(w1,4*h1,w1,5*h1));
    this->addLineSegment(LineSegment(0,6*h1,6*w1,6*h1));
    this->addLineSegment(LineSegment(w1,5*h1,width,5*h1));
    this->addLineSegment(LineSegment(6*w1,6*h1,6*w1,height));
    Point p;
    qsrand(QTime::currentTime().msec());
    int random1 = qrand() %2;
    if (random1) {
        p.x = 0.5*w1;
        p.y = 0.5*h1;
    } else {
        p.x = width-0.5*w1;
        p.y = height-0.5*h1;
    }

    this->bomb.setPoint(p);
}
