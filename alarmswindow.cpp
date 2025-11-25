#include "alarmswindow.h"
#include "addwindow.h"
#include "mainwindow.h"
#include "ui_alarmswindow.h"

#include <chrono>
#include <QTime>
#include <memory>

AlarmsWindow::AlarmsWindow(QWidget *parent) : QDialog{ parent }, ui{ new Ui::AlarmsWindow }
{
    ui->setupUi(this);
    connect(this->ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startAlarm()));
}

AlarmsWindow::~AlarmsWindow()
{
    delete ui;
}

void AlarmsWindow::startAlarm()
{
    const std::chrono::hours hours{ this->ui->hours->value() };
    const std::chrono::minutes minutes{ this->ui->minutes->value() };
    const std::chrono::seconds seconds{ this->ui->seconds->value() };
    const std::chrono::milliseconds msecAlarmTime{
        std::chrono::duration_cast<std::chrono::milliseconds>(hours)
        + std::chrono::duration_cast<std::chrono::milliseconds>(minutes)
        + std::chrono::duration_cast<std::chrono::milliseconds>(seconds)
    };

    auto *addwindow = qobject_cast<AddWindow *>(this->parentWidget());
    const auto documentPath = addwindow->documentPath();

    auto *mainwindow = qobject_cast<MainWindow *>(addwindow->parentWidget());

    const auto msecSinceStartOfDay =
            std::chrono::milliseconds{ QTime::currentTime().msecsSinceStartOfDay() };
    const auto msecTimer = msecAlarmTime - msecSinceStartOfDay;

    if (msecTimer > std::chrono::milliseconds::zero()) {
        mainwindow->alarmsListAddItem(std::make_unique<Timer>(msecTimer));
        AlarmsWindow::accept();
        return;
    }

    const auto msecNextDayTimer = msecTimer
            + std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::hours{ 24 });
    mainwindow->alarmsListAddItem(std::make_unique<Timer>(msecNextDayTimer, documentPath));

    addwindow->resetPath();

    AlarmsWindow::accept();
}
