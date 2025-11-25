#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <chrono>
#include <memory>
#include <QDateTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMessageBox>
#include <QSlider>
#include <QDesktopServices>
#include <qdir.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{ parent },
      ui{ new Ui::MainWindow },
      player{ new QMediaPlayer },
      audioOutput{ new QAudioOutput }
{
    ui->setupUi(this);
    this->ui->doNotDisturb->setChecked(false);

    this->player->setAudioOutput(this->audioOutput);
    //this->player->setSource(QUrl::fromLocalFile("./Resources/timer-ended.mp3"));
    qDebug() << QDir::currentPath();
    this->player->setSource(QUrl::fromLocalFile(QFileInfo("../../Resources/timer-ended.mp3").absoluteFilePath()));
    this->audioOutput->setVolume(this->ui->volumeSlider->value() / 100.);

    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(createAddWindow()));
    connect(this->ui->pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseSelected()));
    connect(this->ui->resumeButton, SIGNAL(clicked(bool)), this, SLOT(resumeSelected()));
    connect(this->ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(adjustVolume()));

    QTimer *timer = new QTimer{ this };
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete audioOutput;
}

void MainWindow::timersListAddItem(std::unique_ptr<Timer> timer)
{
    timer->elapsedStart();
    const auto &remainingMsec = timer->remaining();
    this->m_timers.emplace_back(std::move(timer));

    const auto remainingSec =
            std::chrono::duration_cast<std::chrono::seconds>(remainingMsec).count();
    const auto &displayTime = QTime{ 0, 0 }.addSecs(remainingSec).toString("hh:mm:ss");
    this->ui->timersList->addItem(displayTime);
}

void MainWindow::alarmsListAddItem(std::unique_ptr<Timer> alarm)
{
    alarm->elapsedStart();
    const auto &remainingMsec = alarm->remaining();
    this->m_alarms.emplace_back(std::move(alarm));

    const auto remainingSec =
            std::chrono::duration_cast<std::chrono::seconds>(remainingMsec).count();
    const auto &displayTime = QTime{ 0, 0 }.addSecs(remainingSec).toString("hh:mm:ss");
    this->ui->alarmsList->addItem(displayTime);
}

void MainWindow::createAddWindow()
{
    AddWindow addWindow{ this };
    addWindow.setModal(true);

    if (!addWindow.exec()) {
        return;
    }
}

void MainWindow::updateTimers()
{
    for (size_t i = 0; i < this->m_timers.size(); i++) {
        auto &timer = this->m_timers[i];
        if (timer->paused()) {
            continue;
        }
        const std::chrono::milliseconds elapsed{ timer->elapsedRestart() };
        timer->setRemaining(timer->remaining() - elapsed);
        if (timer->remaining() <= std::chrono::milliseconds{ 0 }) {
            timer->remaining() = std::chrono::milliseconds{ 0 };
            if (!this->ui->doNotDisturb->isChecked()) {
                this->player->play();
            }

            QMessageBox msgBox;
            msgBox.setText("Timer has expired");
            msgBox.exec();
            if (!timer->documentPath().isEmpty()) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(timer->documentPath()));
            }

            this->m_timers.erase(m_timers.begin() + i);
            this->ui->timersList->takeItem(i);
            i--;
            continue;
        }

        auto *item = ui->timersList->item(i);
        const auto remaining =
                std::chrono::duration_cast<std::chrono::seconds>(timer->remaining()).count();
        const auto &displayTime = QTime{ 0, 0 }.addSecs(remaining).toString("hh:mm:ss");
        this->ui->timersList->item(i)->setText(displayTime);
    }
}

void MainWindow::updateAlarms()
{
    for (size_t i = 0; i < this->m_alarms.size(); i++) {
        auto &alarm = this->m_alarms[i];
        if (alarm->paused()) {
            continue;
        }

        const std::chrono::milliseconds elapsed{ alarm->elapsedRestart() };
        alarm->setRemaining(alarm->remaining() - elapsed);
        if (alarm->remaining() <= std::chrono::milliseconds{ 0 }) {
            alarm->remaining() = std::chrono::milliseconds{ 0 };
            if (!this->ui->doNotDisturb->isChecked()) {
                this->player->play();
            }
            QMessageBox msgBox;
            msgBox.setText("Timer has expired");
            msgBox.exec();
            if (!alarm->documentPath().isEmpty()) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(alarm->documentPath()));
            }

            this->m_alarms.erase(m_alarms.cbegin() + i);
            this->ui->alarmsList->takeItem(i);
            i--;
            continue;
        }

        auto *item = ui->alarmsList->item(i);
        const auto remaining =
                std::chrono::duration_cast<std::chrono::seconds>(alarm->remaining()).count();
        const auto &displayTime = QTime{ 0, 0 }.addSecs(remaining).toString("hh:mm:ss");
        this->ui->alarmsList->item(i)->setText(displayTime);
    }
}

void MainWindow::update()
{
    this->updateTimers();
    this->updateAlarms();
}

void MainWindow::pauseTimers()
{
    for (size_t i = 0; i < this->m_timers.size(); i++) {
        if (this->ui->timersList->item(i)->isSelected()) {
            this->m_timers.at(i)->pause();
        }
    }
}
void MainWindow::resumeTimers()
{
    for (size_t i = 0; i < this->m_timers.size(); i++) {
        if (this->ui->timersList->item(i)->isSelected()) {
            this->m_timers.at(i)->resume();
        }
    }
}
void MainWindow::pauseAlarms()
{
    for (size_t i = 0; i < this->m_alarms.size(); i++) {
        if (this->ui->alarmsList->item(i)->isSelected()) {
            this->m_alarms.at(i)->pause();
        }
    }
}
void MainWindow::resumeAlarms()
{
    for (size_t i = 0; i < this->m_alarms.size(); i++) {
        if (this->ui->alarmsList->item(i)->isSelected()) {
            this->m_alarms.at(i)->resume();
        }
    }
}

void MainWindow::pauseSelected()
{
    this->pauseTimers();
    this->pauseAlarms();
}
void MainWindow::resumeSelected()
{
    this->resumeTimers();
    this->resumeAlarms();
}
void MainWindow::adjustVolume()
{
    this->audioOutput->setVolume(this->ui->volumeSlider->value() / 100.);
}
