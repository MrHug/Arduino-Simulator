#ifndef IRSENSORTHREAD_H
#define IRSENSORTHREAD_H

#include <qthread.h>
#include "irsensor.h"
#include <string.h>

class IRSensorThread : public QThread
{
public:
    IRSensorThread(QObject *parent, IRSensor *sensor, std::string fileName);
    void run();

    int filePointer;
    std::string fileName;
    IRSensor *sensor;
    bool updated;
};

#endif // IRSENSORTHREAD_H
