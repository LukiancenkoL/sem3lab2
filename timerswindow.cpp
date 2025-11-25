#include "timerswindow.h"
#include "ui_timerswindow.h"
#include "mainwindow.h"
#include "addwindow.h"

#include <chrono>
#include <QTime>
#include <memory>

TimersWindow::TimersWindow(QWidget *parent) : QDialog{ parent }, ui{ new Ui::TimersWindow }
{
    ui->setupUi(this);
    connect(this->ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startTimer()));
}

TimersWindow::~TimersWindow()
{
    delete ui;
}

void TimersWindow::startTimer()
{
    const std::chrono::hours hours{ this->ui->hours->value() };
    const std::chrono::minutes minutes{ this->ui->minutes->value() };
    const std::chrono::seconds seconds{ this->ui->seconds->value() };
    const std::chrono::milliseconds milliseconds{
        std::chrono::duration_cast<std::chrono::milliseconds>(hours)
        + std::chrono::duration_cast<std::chrono::milliseconds>(minutes)
        + std::chrono::duration_cast<std::chrono::milliseconds>(seconds)
    };

    auto *addwindow = qobject_cast<AddWindow *>(this->parentWidget());
    const auto documentPath = addwindow->documentPath();
    auto *mainwindow = qobject_cast<MainWindow *>(addwindow->parentWidget());

    mainwindow->timersListAddItem(std::make_unique<Timer>(milliseconds, documentPath));
    addwindow->resetPath();

    TimersWindow::accept();
}
