#include "taskswitchthread.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


TaskSwitchThread::TaskSwitchThread(QObject *parent, TaskSwitch *ts, std::string fileName) : QThread(parent)
{   this->ts = ts;
    this->fileName = fileName;
    this->updated = false;
}
void TaskSwitchThread::run() {
    printf("Started running thread\n");
    filePointer = open(fileName.c_str(), O_WRONLY);
    printf("Opened file for sensor.\n");
    while(1) {
        while(!this->updated) {msleep(1);}
        //printf("Writing new value for sensor %d\n", this->sensor->num);
        this->updated = false;
        int distance = this->ts->getValue();
        write(this->filePointer, &distance, 4);
    }
}
