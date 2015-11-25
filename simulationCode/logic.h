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

#define bool int
#define false 0
#define true 1

int digitalRead(int);
int analogRead(int);
void delay(int);

void task1();
void task2();
void task3();

#endif
