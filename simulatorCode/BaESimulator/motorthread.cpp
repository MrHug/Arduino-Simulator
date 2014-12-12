#include "motorthread.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



MotorThread::MotorThread(QObject *parent, Motor *motor, std::string fileName) :
        QThread(parent)
{
   this->motor = motor;
   this->fileName = fileName;
}

void MotorThread::run() {
    printf("Started running Motor thread\n");
    filePointer = open(fileName.c_str(), O_RDONLY);
    printf("Opened file for motor.\n");
    while(1) {
        int speed;
        if (read(filePointer, &speed, sizeof(int)) == sizeof(int)) {
            if (this->motor->speed != speed) {
                printf("Updating motor %d speed to become %d\n", this->motor->type, speed);
                this->motor->speed = speed;
            }
        }
    }
}
