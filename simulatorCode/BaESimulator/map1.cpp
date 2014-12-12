#include "map1.h"

Map1::Map1(double width, double height) : Map(width, height)
{
    double w = width/3;
    double h = height/3;
    this->addLineSegment(LineSegment(0,0,w,h));
    this->addLineSegment(LineSegment(w,h,w,2*h));
    this->addLineSegment(LineSegment(w,2*h,0,height));
    this->addLineSegment(LineSegment(width, 0, 2*w,h));
    this->addLineSegment(LineSegment(2*w, h, 2*w, 2*h));
    this->addLineSegment(LineSegment(2*w,2*h,width,height));
    this->bomb.setPoint(Point(w-w/3,h-(2*h)/3));
}
