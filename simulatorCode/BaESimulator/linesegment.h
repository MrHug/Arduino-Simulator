#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "line.h"

class LineSegment : public Line
{
public:
    LineSegment();
    LineSegment(Point start, Point end);
    LineSegment(double x1, double y1, double x2, double y2);

    bool isIntersect(Line that);
    bool containsPoint(Point p);
    double length();

    Point start, end;
private:

};

#endif // LINESEGMENT_H
