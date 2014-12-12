CC = gcc
CFLAGS= -std=c99 -W -Wall -I. -g -O3 -fPIC
DEPS = motors.h ussensor.h irsensor.h logic.h Makefile
OFILESBASIC = motors.o ussensor.o irsensor.o
OFILES = ${OFILESBASIC} logic.o

all: arduinoSim

arduinoSim: logic.o simLib.so
	gcc -o $@ $^ ${CFLAGS} -lpthread 

simLib.so: ${OFILESBASIC} 
	gcc -shared  -o $@ $^ 
	

logic.c: logic.ino
	./converter.py logic.ino

%.o: %.c
	$(CC) -D _BSD_SOURCE -c -o $@ $< ${CFLAGS}

clean:
	rm arduinoSim
	rm simLib.so
	rm -rf ${OFILES}
	rm -rf logic.c 

moveToBuildFolder:
	rm ../simulatorCode/build*/simFiles -rf
	cp . ../simulatorCode/build-BaESimulator-Desktop-Debug/simFiles -r

.PHONY: all clean moveToBuildFolder
