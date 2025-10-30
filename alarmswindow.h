#ifndef ALARMSWINDOW_H
#define ALARMSWINDOW_H

#include <QWidget>

namespace Ui {
class alarmsWindow;
}

class alarmsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit alarmsWindow(QWidget *parent = nullptr);
    ~alarmsWindow();

private:
    Ui::alarmsWindow *ui;
};

#endif // ALARMSWINDOW_H
