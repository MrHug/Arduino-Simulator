#ifndef LINE_H
#define LINE_H

#include "point.h"


// Line in the form Ax + By + C = 0
class Line
{
public:
    Line(double a, double b, double c);
    Line(Point p, Point q);
    Line(double x1, double y1, double x2, double y2);

    double getAcuteAngleToYAxis();


    // Returns true iff this intersects that.
    virtual bool isIntersect(Line that);
    // Returns the point of the intersection with that, or NULL if none.
    Point getIntersect(Line that);
    // Returns the line that is perpendicular to this and goes through p.
    Line perpendicular(Point p);

    // Returns true iff this line contains the point p.
    virtual bool containsPoint(Point p);
    // Calculates the perpendicular distance to the point.
    double distanceToPoint(Point p);

    // Returns the y to go with p->x, or p->y if no such y is found.
    // Does not change p.
    double calcY(Point p);

    double a;
    double b;
    double c;
};

#endif // LINE_H
