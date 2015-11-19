#include "simulator.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "map0.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "map4.h"
#include "qpainter.h"
#include "qstring.h"
#include <qmessagebox.h>

#define TIMER_INTERVAL 100 //MS

Simulator::Simulator(SimulatorWindow *parent) :
    QGroupBox(parent)
{
    setUpGuiStuff(parent);
    createFifos();
    robot = new Robot();
    map = new Map0(2*CENTER_X, 2*CENTER_Y);
    draw();
}

Simulator::~Simulator() {
    this->cleanup();
    delete robot;
    delete map;
}

void Simulator::cleanup() {
    this->parent->addLog("Cleaning simulator");
    int x = system("ps -Af | grep ./arduinoSim | awk '{ print $2 }' | head -n 1 | xargs kill");
    this->parent->addLog(QString("ps kill output: %1").arg(x));
    motorThreadLeft->terminate();
    motorThreadRight->terminate();
    for (int i = US_SENSOR_0; i< NUMBER_OF_US_SENSORS; i++) {
        usSensorThreads[i]->terminate();
    }
    for (int i = IR_SENSOR_0; i< NUMBER_OF_IR_SENSORS; i++) {
        irSensorThreads[i]->terminate();
    }
    taskSwitchTread->terminate();
}

bool Simulator::startFromFile(QString &fileName) {
    this->parent->addLog(QString("Starting from file %1").arg(fileName));
    QString cmd = QString("cp %1 ./simFiles/tasks.ino").arg(fileName);
    int x = system(cmd.toStdString().c_str());
    this->parent->addLog(QString("Result of cp: %1").arg(x));
    x = system("cd simFiles && make");
    this->parent->addLog(QString("Result of make: %1").arg(x));
    if (x == 0) {
        x = system("./arduinoSim &");
        if (x == 0) {
            createThreads();
            updateSensors();
        } else {
            this->parent->addLog(QString("Can not start simulation. Ask a TA for assistance"));
        }
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","The code provided here can not be compiled! Check the Arduino error messages");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
    return x == 0;
}

void Simulator::start() {
    timerId = this->startTimer(TIMER_INTERVAL);
}

void Simulator::step() {
    robot->move();
    bool collided = checkCollision();
    updateSensors();
    draw();
    parent->updateInformation();
    if (collided) {
        printf("Collided, so stopping\n");
        parent->addLog("Collided with wall, stopping simulation");
        this->stop();
    }
}

void Simulator::stop() {
    this->killTimer(timerId);
}

void Simulator::reset() {
    this->stop();
    this->cleanup();
    this->setMap(mapNum);
}

void Simulator::setMap(int mapNum) {
    delete this->map;
    this->parent->addLog("Resetting Map\n");
    this->robot->resetPoints();
    switch (mapNum) {
        case 0:
            this->map = new Map0(2*CENTER_X, 2*CENTER_Y);
            break;
        case 1:
            this->map = new Map1(2*CENTER_X, 2*CENTER_Y);
            break;
        case 2:
            this->map = new Map2(2*CENTER_X, 2*CENTER_Y);
            break;
        case 3:
            this->map = new Map3(2*CENTER_X, 2*CENTER_Y);
            break;
        case 4:
            this->map = new Map4(2*CENTER_X, 2*CENTER_Y);
            break;
    }
    this->mapNum = mapNum;
    this->draw();
}

void Simulator::setUpGuiStuff(SimulatorWindow *parent) {
    setParent(parent);
    setGeometry(10,60,2*CENTER_X,2*CENTER_Y);
    setVisible(true);
    setTitle("Map");
    QPalette pal(palette());
    pal.setColor(QPalette::Background,Qt::darkGray);
    setPalette(pal);
    setAutoFillBackground(true);

    this->parent = parent;
}

void Simulator::createFifos() {
    mkfifo("MotorL.pipe", 0666);
    mkfifo("MotorR.pipe", 0666);
    for (int i = US_SENSOR_0; i< NUMBER_OF_US_SENSORS; i++) {
        QString fileName = "USSensor";
        fileName += QString::number(i);
        fileName += ".pipe";
        mkfifo(fileName.toStdString().c_str(), 0666);
    }
    for (int i = IR_SENSOR_0; i< NUMBER_OF_IR_SENSORS; i++) {
        QString fileName = "IRSensor";
        fileName += QString::number(i);
        fileName += ".pipe";
        mkfifo(fileName.toStdString().c_str(), 0666);
    }
    mkfifo("taskSwitch.pipe",0666);
}

void Simulator::createThreads() {
    motorThreadLeft = new MotorThread(NULL,&robot->leftMotor, "MotorL.pipe");
    motorThreadRight = new MotorThread(NULL,&robot->rightMotor, "MotorR.pipe");
    motorThreadLeft->start();
    motorThreadRight->start();
    for (int i = US_SENSOR_0; i< NUMBER_OF_US_SENSORS; i++) {
        QString fileName = "USSensor";
        fileName += QString::number(i);
        fileName += ".pipe";
        usSensorThreads[i] = new USSensorThread(NULL, robot->usSensors[i], fileName.toStdString().c_str());
        usSensorThreads[i]->start();
    }

    for (int i = IR_SENSOR_0; i< NUMBER_OF_IR_SENSORS; i++) {
        QString fileName = "IRSensor";
        fileName += QString::number(i);
        fileName += ".pipe";
        irSensorThreads[i] = new IRSensorThread(NULL, robot->irSensors[i], fileName.toStdString().c_str());
        irSensorThreads[i]->start();
    }
    taskSwitchTread = new TaskSwitchThread(NULL, &robot->taskSwitch, "taskSwitch.pipe");
    taskSwitchTread->start();
}

bool Simulator::checkCollision() {
    Point p[4];
    this->getRobotPoints(p);
    LineSegment robotSegments[4] = {
        LineSegment(p[0], p[1]),
        LineSegment(p[1],p[2]),
        LineSegment(p[2],p[3]),
        LineSegment(p[3],p[0])
    };

    LineSegment bombSegments[4];
    this->map->bomb.getLineSegments(bombSegments);

    for (std::vector<LineSegment>::iterator it = map->lines.begin();
         it != map->lines.end(); ++it) {
        for (int i = 0; i < 4; i++) {
            LineSegment robotSegment = robotSegments[i];
            LineSegment mapSegment = *it;
            if (robotSegment.isIntersect(mapSegment) && mapSegment.isIntersect(robotSegment)) {
                return true;
            }
        }
    }

    for (int i = 0; i<4; i++) {
        LineSegment robotSegment = robotSegments[i];
        for (int j = 0; j<4; j++) {
            LineSegment bombSegment = bombSegments[j];
            if (robotSegment.isIntersect(bombSegment) && bombSegment.isIntersect(robotSegment)) {
                return true;
            }
        }
    }

    return false;
}

void Simulator::draw() {
    update();
}

void Simulator::paintEvent(QPaintEvent *event) {
    if (event) {
     drawMap();
     drawRobot();
    }
}

void Simulator::timerEvent(QTimerEvent *event) {
    if (event) {
        this->step();
    }
}

void Simulator::drawMap() {
    QPainter painter(this);
    painter.setPen(QPen(QBrush(Qt::blue), 5));
    //painter.setBrushOrigin(CENTER_X,CENTER_Y);

    for (std::vector<LineSegment>::iterator it = map->lines.begin();
         it != map->lines.end(); ++it) {
        LineSegment seg = *it;
        QPoint p0(seg.start.x, 2*CENTER_Y - seg.start.y);
        QPoint p1(seg.end.x, 2*CENTER_Y - seg.end.y);
        //printf("Drawing line from (%f,%f) to (%f,%f)\n",seg.start.x, seg.start.y,seg.end.x, seg.start.y);
        painter.drawLine(p0,p1);
    }

    painter.setPen(QPen(QBrush(Qt::red), BOMB_DIMENSION));
    Point bomb = map->bomb.getPoint();
    painter.drawPoint(bomb.x, 2*CENTER_Y - bomb.y);
}

void Simulator::drawRobot() {
    QPainter painter(this);
    painter.setBrush(Qt::SolidPattern);
    QPoint p[4];
    getRobotPoints(p);
    painter.drawPolygon(p,4);

    //Draw a green line to represent the front of the robot
    painter.setPen(Qt::green);
    painter.drawLine(p[0],p[1]);
}


void Simulator::updateSensors() {
    Point robotCenter = robot->getCenter();
    robotCenter.x += CENTER_X;
    robotCenter.y += CENTER_Y;
    robot->updateSensors(robotCenter, map);
    for (int i = US_SENSOR_0; i< NUMBER_OF_US_SENSORS; i++) {
        usSensorThreads[i]->updated = true;
    }
    for (int i = IR_SENSOR_0; i< NUMBER_OF_IR_SENSORS; i++) {
        irSensorThreads[i]->updated = true;
    }
    taskSwitchTread->updated = true;
}

void Simulator::getRobotPoints(QPoint p[]) {
    Point *q = robot->getPoints();
    for (int i= 0; i < 4; i++) {
        p[i].setX(q[i].x + CENTER_X);
        p[i].setY(-q[i].y + CENTER_Y);
    }
}

void Simulator::getRobotPoints(Point p[]) {
    Point *q = robot->getPoints();
    for (int i= 0; i < 4; i++) {
        p[i].x = (q[i].x + CENTER_X);
        p[i].y = (q[i].y + CENTER_Y);
    }
}


