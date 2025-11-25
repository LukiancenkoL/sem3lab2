#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <qtimer.h>
#include <vector>
#include <QTime>
#include <QTimer>
#include <QMediaPlayer>
#include "timer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void timersListAddItem(std::unique_ptr<Timer> timer);
    void alarmsListAddItem(std::unique_ptr<Timer> alarm);

private slots:
    void createAddWindow();
    void update();
    void pauseSelected();
    void resumeSelected();
    void adjustVolume();

private:
    void updateTimers();
    void updateAlarms();

    void pauseTimers();
    void resumeTimers();

    void pauseAlarms();
    void resumeAlarms();

private:
    std::vector<std::unique_ptr<Timer>> m_timers{};
    std::vector<std::unique_ptr<Timer>> m_alarms{};
    Ui::MainWindow *ui;
    QMediaPlayer *player{};
    QAudioOutput *audioOutput{};
};
#endif // MAINWINDOW_H
