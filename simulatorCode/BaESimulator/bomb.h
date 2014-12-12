#ifndef BOMB_H
#define BOMB_H

#include <point.h>
#include <linesegment.h>

#define BOMB_DIMENSION 12

class Bomb
{
public:
    Bomb();

    Point getPoint() {return point;}
    void setPoint(Point p) {this->point = p;}
    void getPoints(Point p[]);
    void getLineSegments(LineSegment segs[]);

private:
    Point point;
};

#endif // BOMB_H
