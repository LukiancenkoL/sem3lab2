#include "timerswindow.h"
#include "ui_timerswindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addwindow.h"
#include "ui_addwindow.h"

#include <chrono>
#include <QTime>

timersWindow::timersWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::timersWindow)
{
    ui->setupUi(this);
    connect(this->ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startTimer()));
}

timersWindow::~timersWindow()
{
    delete ui;
}

void timersWindow::startTimer ()
{
    std::chrono::hours hours {this->ui->hours->value()};
    std::chrono::minutes minutes {this->ui->minutes->value()};
    std::chrono::seconds seconds {this->ui->seconds->value()};
    std::chrono::milliseconds milliseconds {std::chrono::duration_cast<std::chrono::milliseconds>(hours) +
                                           std::chrono::duration_cast<std::chrono::milliseconds>(minutes) +
                                           std::chrono::duration_cast<std::chrono::milliseconds>(seconds)};

    auto *addwindow = qobject_cast<addWindow*>(this->parentWidget());
    auto *mainwindow = qobject_cast<mainWindow*>(addwindow->parentWidget());

    mainwindow->timers_list_add_item(Timer{milliseconds});

    timersWindow::accept();
}

