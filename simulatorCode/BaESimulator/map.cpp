#include "map.h"

Map::Map(double width, double height)
{
    this->width = width;
    this->height = height;

    // Create the border of the map
    Point leftBottom(0,0);
    Point rightBottom(width,0);
    Point leftTop (0, height);
    Point rightTop (width, height);
    LineSegment top(leftTop, rightTop);
    LineSegment left(leftTop, leftBottom);
    LineSegment right(rightTop, rightBottom);
    LineSegment bottom(leftBottom, rightBottom);
    this->addLineSegment(top);
    this->addLineSegment(left);
    this->addLineSegment(right);
    this->addLineSegment(bottom);
    this->bomb.setPoint(Point(0.5*width, 0.75*height));
}

void Map::addLineSegment(LineSegment segment) {
    this->lines.push_back(segment);
}
