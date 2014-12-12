#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator;

#include "robot.h"
#include "map.h"
#include "qgroupbox.h"
#include "motorthread.h"
#include "ussensorthread.h"
#include "irsensorthread.h"
#include "simulatorwindow.h"

#define CENTER_X 350
#define CENTER_Y 300

class Simulator : public QGroupBox
{
public:
    Simulator(SimulatorWindow *parent);
    ~Simulator();

    bool startFromFile(QString &fileName);
    void start();
    void step();
    void stop();
    void setMap(int mapNum);
    Robot *robot;
private:

    void setUpGuiStuff(SimulatorWindow *parent);
    void createFifos();
    void createThreads();
    bool checkCollision();
    void draw();
    void drawMap();
    void drawRobot();
    void updateSensors();
    void getRobotPoints(QPoint p[]);
    void getRobotPoints(Point p[]);

    Map *map;

    MotorThread *motorThreadLeft, *motorThreadRight;
    USSensorThread *usSensorThreads[NUMBER_OF_US_SENSORS];
    IRSensorThread *irSensorThreads[NUMBER_OF_IR_SENSORS];
    SimulatorWindow *parent;
    int timerId;

public slots:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // SIMULATOR_H
