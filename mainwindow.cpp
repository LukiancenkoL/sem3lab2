#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <chrono>
#include <qdatetime.h>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("../icon/icon.ico"));
    this->ui->doNotDisturb->setChecked(false);
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(createAddWindow()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAllTimers()));
    timer->start(1000);
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::timers_emplace_back(Timer &&timer) {
    timers.push_back(timer);
}
void mainWindow::alarms_emplace_back(Timer &&alarm) {
    alarms.emplace_back(alarm);
}

void mainWindow::timers_list_add_item(Timer &&timer) {
    timer.elaplsed.start();
    const auto& remaining_msec = timer.remaining;
    this->timers_emplace_back(std::move(timer));
    const auto remaining_sec = std::chrono::duration_cast<std::chrono::seconds>(remaining_msec).count();
    const auto& display_time = QTime{0,0}.addSecs(remaining_sec).toString("hh:mm:ss");
    this->ui->timersList->addItem(display_time);
}

void mainWindow::createAddWindow()
{
    addWindow AddWindow{this};
    AddWindow.setModal(true);

    if (!AddWindow.exec())
    {
        // for (const auto& a:this->timers)
        // {
        //     QMessageBox::warning(this, "Помилка", "Введений час не може бути рівним нулю");
        // }
        return;
    }

}
void mainWindow::updateAllTimers()
{
    for (size_t i = 0; i < this->timers.size(); i++) {
        auto& timer = this->timers[i];
        if (timer.paused){
            continue;
        }
        const std::chrono::milliseconds elapsed{timer.elaplsed.restart()};
        timer.remaining -= elapsed;
        if (timer.remaining <= std::chrono::milliseconds{0}) {
            timer.remaining = std::chrono::milliseconds{0};
            this->ui->timersList->item(i)->setText("fin");
            //todo handle timer remove
        }
        auto* item = ui->timersList->item(i);
        const auto remaining_sec = std::chrono::duration_cast<std::chrono::seconds>(timer.remaining).count();
        const auto& display_time = QTime{0,0}.addSecs(remaining_sec).toString("hh:mm:ss");
        this->ui->timersList->item(i)->setText(display_time);
    }
}
