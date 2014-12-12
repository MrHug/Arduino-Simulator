#include "line.h"

#include <math.h>
#include "commonfunctions.h"

Line::Line(double a, double b, double c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

Line::Line(Point p, Point q) {
    this->a = p.y - q.y;
    this->b = q.x - p.x;
    this->c = -(this->a*p.x + this->b*p.y);
}

Line::Line(double x1, double y1, double x2, double y2) {
    this->a = y1 - y2;
    this->b = x2 - x1;
    this->c = -(this->a*x1 + this->b*y1);
}

double Line::getAcuteAngleToYAxis() {
    if (doubleEquals(b,0)) {
        return 0;
    }
    return atan(-this->a/this->b);
}

bool Line::isIntersect(Line that) {
    return !doubleEquals(this->a*that.b - that.a *this->b,0);
}

//http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=geometry2
Point Line::getIntersect(Line that) {
    double det = this->a*that.b - that.a*this->b;
    if (doubleEquals(det,0)) {
        return Point(0,0); // Should use isIntersect to find this is invalid.
    } else {
        return Point((this->b*that.c - that.b*this->c)/det,
                         (that.a*this->c-this->a*that.c)/det);
    }
}

Line Line::perpendicular(Point p) {
    double d = (a-b)*p.x + (b-a)*p.y + c;
    return Line(this->b, -this->a, d);
}

bool Line::containsPoint(Point p) {
    return doubleEquals(this->a*p.x + this->b*p.y, -this->c);
}

double Line::distanceToPoint(Point p) {
    return (this->a*p.x + this->b*p.y + c)/
           (this->a*this->a + this->b*this->b);
}

double Line::calcY(Point p) {
    if (doubleEquals(b,0)) {
        return p.y;
    } else {
        return (-c - a*p.x)/b;
    }
}
