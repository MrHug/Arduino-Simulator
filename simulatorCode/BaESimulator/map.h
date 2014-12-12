#ifndef MAP_H
#define MAP_H

#include <vector>
#include "linesegment.h"
#include "bomb.h"

class Map
{
public:
    Map(double width, double height);

    void addLineSegment(LineSegment segment);
    std::vector<LineSegment> lines;
    Bomb bomb;

private:

    double width;
    double height;

};

#endif // MAP_H
