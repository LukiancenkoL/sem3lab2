#ifndef TIMERSWINDOW_H
#define TIMERSWINDOW_H

#include <QTimer>
#include <QDialog>


namespace Ui {
class timersWindow;
}

class timersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit timersWindow(QWidget *parent = nullptr);
    ~timersWindow();

private slots:
    void startTimer();

private:
    Ui::timersWindow *ui;
};

#endif // TIMERSWINDOW_H
