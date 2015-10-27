#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QMainWindow>
class SimulatorWindow;

#include "simulator.h"
#include <qspinbox.h>

namespace Ui {
class SimulatorWindow;
}
class SimulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();
    void updateInformation();

private slots:
    void on_BtnStart_clicked();
    void on_BtnStop_clicked();
    void on_BtnStep_clicked();

    void on_SpBoxUS0_editingFinished();
    void on_SpBoxUS1_editingFinished();
    void on_SpBoxUS2_editingFinished();

    void on_SpBoxIR0_editingFinished();
    void on_SpBoxIR1_editingFinished();
    void on_SpBoxIR2_editingFinished();
    void on_SpBoxIR3_editingFinished();
    void on_SpBoxIR4_editingFinished();
    void on_SpBoxIR5_editingFinished();


    void on_BtnOpen_clicked();

    void on_btnMap0_clicked();

    void on_btnMap1_clicked();

    void on_btnMap2_clicked();

    void on_btnMap3_clicked();

private:
    Ui::SimulatorWindow *ui;

    Simulator *sim;

    void setAngle(QSpinBox *box, Sensor *sensor);
    void setAngles();
};

#endif // SIMULATORWINDOW_H


