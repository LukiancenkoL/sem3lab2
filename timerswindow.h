#ifndef TIMERSWINDOW_H
#define TIMERSWINDOW_H

#include <QWidget>

namespace Ui {
class timersWindow;
}

class timersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit timersWindow(QWidget *parent = nullptr);
    ~timersWindow();

private:
    Ui::timersWindow *ui;
};

#endif // TIMERSWINDOW_H
