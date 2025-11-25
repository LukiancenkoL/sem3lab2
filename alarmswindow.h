#ifndef ALARMSWINDOW_H
#define ALARMSWINDOW_H

#include <QDialog>

namespace Ui {
class AlarmsWindow;
}

class AlarmsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmsWindow(QWidget *parent = nullptr);
    ~AlarmsWindow();

private slots:
    void startAlarm();

private:
    Ui::AlarmsWindow *ui;
};

#endif // ALARMSWINDOW_H
