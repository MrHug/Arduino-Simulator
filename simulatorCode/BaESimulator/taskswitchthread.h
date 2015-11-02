#ifndef TASKSWITCHTHREAD_H
#define TASKSWITCHTHREAD_H

#include <qthread.h>
#include "taskswitch.h"
#include <string.h>

class TaskSwitchThread : public QThread
{
public:
    TaskSwitchThread(QObject *parent, TaskSwitch *ts, std::string fileName);
    void run();

    int filePointer;
    std::string fileName;
    TaskSwitch *ts;
    bool updated;
};

#endif // TASKSWITCHTHREAD_H
