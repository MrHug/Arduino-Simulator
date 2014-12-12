#include "map0.h"

#include <qglobal.h>
#include <QTime>

Map0::Map0(double width, double height) : Map(width, height)
{
    Point p;
    qsrand(QTime::currentTime().msec());
    int random1 = qrand() %2;
    int random2 = qrand() %2;
    p.x = (width*3*random1 + width)/5;
    p.y = (height*3*random2 + height)/5;
    this->bomb.setPoint(p);
}
