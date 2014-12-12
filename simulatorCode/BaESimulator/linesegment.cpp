#include "linesegment.h"

#include <math.h>
#include <algorithm>
#include "commonfunctions.h"

LineSegment::LineSegment() : Line(0,0,1,1) {
    // Simple line x = y is the default.
}

LineSegment::LineSegment(Point start, Point end) : Line(start, end)
{
    this->start = start;
    this->end = end;
}

LineSegment::LineSegment(double x1, double y1, double x2, double y2) : Line(x1,y1,x2,y2){
    this->start.x = x1;
    this->start.y = y1;
    this->end.x = x2;
    this->end.y = y2;
}

bool LineSegment::isIntersect(Line that) {
    bool result = Line::isIntersect(that);
    bool res2 = this->containsPoint(this->getIntersect(that));
    return result && res2;
}

bool LineSegment::containsPoint(Point p) {
    bool result = Line::containsPoint(p);
    bool res2 = (p.x >= std::min(start.x, end.x) && p.x <= std::max(start.x, end.x)) || (doubleEquals(p.x, start.x) || doubleEquals(p.x, end.x));
    bool res3 = (p.y >= std::min(start.y, end.y) && p.y <= std::max(start.y, end.y)) || (doubleEquals(p.y, start.y) || doubleEquals(p.y, end.y));
    return result && res2 && res3;
}

double LineSegment::length() {
    double dx = this->start.x - this->end.x;
    double dy = this->start.y - this->end.y;
    return sqrt(dx*dx + dy*dy);
}
