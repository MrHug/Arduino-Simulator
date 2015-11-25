#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"

#include <qfiledialog.h>
#include <qdebug.h>

SimulatorWindow::SimulatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
    sim = new Simulator(this);
    setAngles();
    updateInformation();
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
    delete sim;
}

void SimulatorWindow::updateInformation() {
    ui->LblUS0V->setText(QString::number(sim->robot->usSensors[0]->getValue()));
    ui->LblUS1V->setText(QString::number(sim->robot->usSensors[1]->getValue()));
    ui->LblUS2V->setText(QString::number(sim->robot->usSensors[2]->getValue()));

    ui->LblIR0V->setText(QString::number(sim->robot->irSensors[0]->getValue()));
    ui->LblIR1V->setText(QString::number(sim->robot->irSensors[1]->getValue()));
    ui->LblIR2V->setText(QString::number(sim->robot->irSensors[2]->getValue()));
    ui->LblIR3V->setText(QString::number(sim->robot->irSensors[3]->getValue()));
    ui->LblIR4V->setText(QString::number(sim->robot->irSensors[4]->getValue()));
    ui->LblIR5V->setText(QString::number(sim->robot->irSensors[5]->getValue()));
}

void SimulatorWindow::on_BtnStart_clicked()
{
    sim->start();
    this->sim->robot->taskSwitch.updateValue(this->ui->spBoxTask->value() -1);
    ui->BtnStart->setEnabled(false);
    ui->BtnStop->setEnabled(true);
    ui->BtnReset->setEnabled(true);
    ui->BtnSoftReset->setEnabled(true);
}
void SimulatorWindow::on_BtnStop_clicked()
{
    sim->stop();
    ui->BtnStart->setEnabled(true);
    ui->BtnStop->setEnabled(false);
}


void SimulatorWindow::on_BtnStep_clicked()
{
    sim->step();
}

void SimulatorWindow::on_SpBoxUS0_editingFinished()
{
    this->setAngle(ui->SpBoxUS0, this->sim->robot->usSensors[0]);
}

void SimulatorWindow::on_SpBoxUS1_editingFinished()
{
    this->setAngle(ui->SpBoxUS1, this->sim->robot->usSensors[1]);
}

void SimulatorWindow::on_SpBoxUS2_editingFinished()
{
    this->setAngle(ui->SpBoxUS2, this->sim->robot->usSensors[2]);
}

void SimulatorWindow::on_SpBoxIR0_editingFinished()
{
    this->setAngle(ui->SpBoxIR0, this->sim->robot->irSensors[0]);
}

void SimulatorWindow::on_SpBoxIR1_editingFinished()
{
    this->setAngle(ui->SpBoxIR1, this->sim->robot->irSensors[1]);
}

void SimulatorWindow::on_SpBoxIR2_editingFinished()
{
    this->setAngle(ui->SpBoxIR2, this->sim->robot->irSensors[2]);
}

void SimulatorWindow::on_SpBoxIR3_editingFinished()
{
    this->setAngle(ui->SpBoxIR3, this->sim->robot->irSensors[3]);
}

void SimulatorWindow::on_SpBoxIR4_editingFinished()
{
    this->setAngle(ui->SpBoxIR4, this->sim->robot->irSensors[4]);
}

void SimulatorWindow::on_SpBoxIR5_editingFinished()
{
    this->setAngle(ui->SpBoxIR5, this->sim->robot->irSensors[5]);
}

void SimulatorWindow::setAngle(QSpinBox *box, Sensor *sensor) {
    double angle = box->value() * PI / 180.0;
    sensor->setAngle(angle);
}

void SimulatorWindow::setAngles() {
    ui->SpBoxUS0->setValue(sim->robot->usSensors[0]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxUS1->setValue(sim->robot->usSensors[1]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxUS2->setValue(sim->robot->usSensors[2]->getAngle() * 180 / PI + 0.5);

    ui->SpBoxIR0->setValue(sim->robot->irSensors[0]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxIR1->setValue(sim->robot->irSensors[1]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxIR2->setValue(sim->robot->irSensors[2]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxIR3->setValue(sim->robot->irSensors[3]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxIR4->setValue(sim->robot->irSensors[4]->getAngle() * 180 / PI + 0.5);
    ui->SpBoxIR5->setValue(sim->robot->irSensors[5]->getAngle() * 180 / PI + 0.5);
}

void SimulatorWindow::on_BtnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Simulation file"), "/tmp", tr("Arduino files (*.ino)"));
    if (fileName.length() > 0) {
        bool startedSim = this->sim->startFromFile(fileName);
        if (startedSim) {
            ui->BtnStart->setEnabled(true);
            ui->BtnStep->setEnabled(true);
            ui->BtnOpen->setEnabled(false);
        }
    }
}

void SimulatorWindow::on_btnMap0_clicked()
{
    this->sim->setMap(0);
}

void SimulatorWindow::on_btnMap1_clicked()
{
    this->sim->setMap(1);
}

void SimulatorWindow::on_btnMap2_clicked()
{
    this->sim->setMap(2);
}

void SimulatorWindow::on_btnMap3_clicked()
{
    this->sim->setMap(3);
}

void SimulatorWindow::addLog(QString string) {
    this->ui->logBox->addItem(string);
}

void SimulatorWindow::on_btnMap4_clicked()
{
    this->sim->setMap(4);
}

void SimulatorWindow::on_spBoxTask_editingFinished()
{
    this->addLog(QString("Task set to %1").arg(this->ui->spBoxTask->value()));
    this->sim->robot->taskSwitch.updateValue(this->ui->spBoxTask->value() -1);
}

void SimulatorWindow::on_spBoxTask_valueChanged(int arg1)
{
    this->addLog(QString("Task set to %1").arg(this->ui->spBoxTask->value()));
    this->sim->robot->taskSwitch.updateValue(this->ui->spBoxTask->value() -1);
}

void SimulatorWindow::on_BtnReset_clicked()
{
    this->sim->reset();
    ui->BtnStart->setEnabled(false);
    ui->BtnStep->setEnabled(false);
    ui->BtnStop->setEnabled(false);
    ui->BtnReset->setEnabled(false);
    ui->BtnSoftReset->setEnabled(false);
    ui->BtnOpen->setEnabled(true);
}


void SimulatorWindow::on_BtnSoftReset_clicked()
{
    this->sim->softReset();
    ui->BtnStart->setEnabled(true);
    ui->BtnStop->setEnabled(false);
}
