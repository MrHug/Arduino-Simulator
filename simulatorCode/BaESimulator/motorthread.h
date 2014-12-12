#ifndef MOTORTHREAD_H
#define MOTORTHREAD_H

#include <string.h>
#include <qthread.h>
#include "motor.h"

class MotorThread : public QThread
{
public:
    MotorThread(QObject *parent, Motor *motor, std::string fileName);
    void run();

    int filePointer;
    std::string fileName;
    Motor *motor;
};

#endif // MOTORTHREAD_H
