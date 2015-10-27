#-------------------------------------------------
#
# Project created by QtCreator 2014-08-11T15:04:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaESimulator
TEMPLATE = app


SOURCES += main.cpp\
        simulatorwindow.cpp \
    robot.cpp \
    line.cpp \
    point.cpp \
    motor.cpp \
    simulator.cpp \
    motorthread.cpp \
    linesegment.cpp \
    map.cpp \
    map1.cpp \
    ussensor.cpp \
    commonfunctions.cpp \
    ussensorthread.cpp \
    bomb.cpp \
    irsensor.cpp \
    sensor.cpp \
    map0.cpp \
    irsensorthread.cpp \
    map2.cpp \
    map3.cpp

HEADERS  += simulatorwindow.h \
    robot.h \
    line.h \
    point.h \
    motor.h \
    simulator.h \
    motorthread.h \
    linesegment.h \
    map.h \
    map1.h \
    ussensor.h \
    commonfunctions.h \
    ussensorthread.h \
    bomb.h \
    irsensor.h \
    sensor.h \
    map0.h \
    irsensorthread.h \
    map2.h \
    map3.h

FORMS    += simulatorwindow.ui
