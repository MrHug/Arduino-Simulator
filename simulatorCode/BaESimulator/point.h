#ifndef POINT_H
#define POINT_H



class Point
{
public:
    Point() {this->x = 0; this->y = 0;}
    Point(double x, double y);
    double x,y;

    void print();

private:

};

#endif // POINT_H
