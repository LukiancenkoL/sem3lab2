#ifndef TIMERSWINDOW_H
#define TIMERSWINDOW_H

#include <QDialog>

namespace Ui {
class TimersWindow;
}

class TimersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TimersWindow(QWidget *parent = nullptr);
    ~TimersWindow();

private slots:
    void startTimer();

private:
    Ui::TimersWindow *ui;
};

#endif // TIMERSWINDOW_H
