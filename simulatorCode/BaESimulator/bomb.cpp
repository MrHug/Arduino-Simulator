#include "bomb.h"

Bomb::Bomb()
{
}

void Bomb::getPoints(Point p[]) {
    p[0].x = point.x-BOMB_DIMENSION/2.0; p[0].y = point.y-BOMB_DIMENSION/2.0;
    p[1].x = point.x-BOMB_DIMENSION/2.0; p[1].y = point.y+BOMB_DIMENSION/2.0;
    p[2].x = point.x+BOMB_DIMENSION/2.0; p[2].y = point.y+BOMB_DIMENSION/2.0;
    p[3].x = point.x+BOMB_DIMENSION/2.0; p[3].y = point.y-BOMB_DIMENSION/2.0;
}

void Bomb::getLineSegments(LineSegment segs[]) {
    Point bombP[4];
    this->getPoints(bombP);
    segs[0] = LineSegment(bombP[0], bombP[1]);
    segs[1] = LineSegment(bombP[1],bombP[2]);
    segs[2] = LineSegment(bombP[2],bombP[3]);
    segs[3] = LineSegment(bombP[3],bombP[0]);
}
