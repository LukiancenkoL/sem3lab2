#include "addwindow.h"
#include "ui_addwindow.h"
#include "timerswindow.h"
#include "alarmswindow.h"

#include <QFileDialog>
#include <QWidget>

AddWindow::AddWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddWindow)
{
    ui->setupUi(this);
    connect(this->ui->addTimer, SIGNAL(clicked(bool)), this, SLOT(createTimerWindow()));
    connect(this->ui->addAlarm, SIGNAL(clicked(bool)), this, SLOT(createAlarmWindow()));
    connect(this->ui->fileSelect, SIGNAL(clicked(bool)), this, SLOT(openFileExplorer()));
}

AddWindow::~AddWindow()
{
    delete ui;
}

QString AddWindow::documentPath() const
{
    return this->m_documentPath;
}

void AddWindow::createTimerWindow()
{
    TimersWindow timerWindow{ this };
    timerWindow.setModal(true);

    if (!timerWindow.exec()) {
        return;
    }
}

void AddWindow::createAlarmWindow()
{
    AlarmsWindow alarmWindow{ this };
    alarmWindow.setModal(true);

    if (!alarmWindow.exec()) {
        return;
    }
}
void AddWindow::openFileExplorer()
{
    this->m_documentPath =
            QFileDialog::getOpenFileName(this, "Select a file to open on completion");
}
void AddWindow::resetPath()
{
    this->m_documentPath = {};
}
