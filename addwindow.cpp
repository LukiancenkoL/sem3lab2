#include "addwindow.h"
#include "ui_addwindow.h"
#include "timerswindow.h"
#include "alarmswindow.h"



#include <QWidget>

addWindow::addWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addWindow)
{
    ui->setupUi(this);
    connect(this->ui->addTimer, SIGNAL(clicked(bool)), this, SLOT(createTimerWindow()));
    connect(this->ui->addAlarm, SIGNAL(clicked(bool)), this, SLOT(createAlarmWindow()));
}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::createTimerWindow()
{
    timersWindow timerWindow{this};
    timerWindow.setModal(true);

    if (!timerWindow.exec())
    {
        return;
    }


}

void addWindow::createAlarmWindow()
{
    alarmsWindow alarmWindow{this};
    alarmWindow.setModal(true);

    if (!alarmWindow.exec())
    {
        return;
    }


}
