#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtimer.h>
#include <vector>
#include <memory>
#include <QTime>
#include <QTimer>
// #include <QVBoxLayout>
// #include <QProcess>
#include "timer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

    void timers_list_add_item(Timer &&timer);
    void alarms_list_add_item(Timer &&alarm);

private slots:
    void createAddWindow();
    void updateAllTimers();


private:
    void timers_emplace_back(Timer &&timer);
    void alarms_emplace_back(Timer &&alarm);

private:
    std::vector<Timer> timers {};
    std::vector<Timer> alarms {};
    Ui::mainWindow *ui;
};
#endif // MAINWINDOW_H
