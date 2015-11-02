CC = gcc
CFLAGS= -std=c99 -W -Wall -I. -g -O3 -fPIC
DEPS = motors.h ussensor.h irsensor.h logic.h Makefile
OFILESBASIC = motors.o ussensor.o irsensor.o logic.o
OFILES = ${OFILESBASIC} tasks.o

all: arduinoSim

arduinoSim: ${OFILES} 
	gcc -o $@ $^ ${CFLAGS} -lpthread 
	cp $@ ..

simLib.so: ${OFILESBASIC} 
	gcc -shared  -o $@ $^ 
	

tasks.c: tasks.ino
	./converter.py tasks.ino

%.o: %.c
	$(CC) -D _BSD_SOURCE -c -o $@ $< ${CFLAGS}

clean:
	rm -f arduinoSim
	rm -f simLib.so
	rm -rf ${OFILES}
	rm -rf tasks.c 

moveToBuildFolder:
	rm ../simulatorCode/build*/simFiles -rf
	cp . ../simulatorCode/build-BaESimulator-Desktop-Debug/simFiles -r
	cp . ../simulatorCode/build-BaESimulator-Delft-Debug/simFiles -r

.PHONY: all clean moveToBuildFolder
