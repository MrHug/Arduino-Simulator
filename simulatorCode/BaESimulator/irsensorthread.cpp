#include "irsensorthread.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


IRSensorThread::IRSensorThread(QObject *parent, IRSensor *sensor, std::string fileName) : QThread(parent)
{
    this->sensor = sensor;
    this->fileName = fileName;
    this->updated = false;
}

void IRSensorThread::run() {
    printf("Started running thread for ir sensor\n");
    filePointer = open(fileName.c_str(), O_WRONLY);
    if (filePointer < 0) {
        printf("Oopsie!\n");
        return;
    }
    printf("Opened file for ir sensor %d.\n", sensor->num);
    while(1) {
        while(!this->updated) {msleep(1);}
        //printf("Writing new value for sensor %d\n", this->sensor->num);
        this->updated = false;
        int distance = sensor->getValue();
        write(this->filePointer, &distance, 4);
    }
}
