#include "ussensorthread.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

USSensorThread::USSensorThread(QObject *parent, USSensor *sensor, std::string fileName) : QThread(parent)
{
    this->sensor = sensor;
    this->fileName = fileName;
    this->updated = false;
}

void USSensorThread::run() {
    printf("Started running thread\n");
    filePointer = open(fileName.c_str(), O_WRONLY);
    printf("Opened file for sensor.\n");
    while(1) {
        while(!this->updated) {msleep(1);}
        //printf("Writing new value for sensor %d\n", this->sensor->num);
        this->updated = false;
        int distance = sensor->getValue();
        write(this->filePointer, &distance, 4);
    }
}
