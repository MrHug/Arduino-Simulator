#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>                                                              
#include <stdio.h>                                                               
#include <unistd.h>
#include "motors.h"
#include "irsensor.h"
#include "ussensor.h"

#define LOW 0
#define HIGH 1

int digitalRead(int);
int analogRead(int);

void task1();
void task2();
void task3();

#endif
