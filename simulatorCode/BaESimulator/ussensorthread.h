#ifndef USSENSORTHREAD_H
#define USSENSORTHREAD_H

#include <qthread.h>
#include "ussensor.h"
#include <string.h>

class USSensorThread : public QThread{
public:
    USSensorThread(QObject *parent, USSensor *sensor, std::string fileName);
    void run();

    int filePointer;
    std::string fileName;
    USSensor *sensor;
    bool updated;
};

#endif // USSENSORTHREAD_H
