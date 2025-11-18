#ifndef ALARMSWINDOW_H
#define ALARMSWINDOW_H

#include <QDialog>

namespace Ui {
class alarmsWindow;
}

class alarmsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit alarmsWindow(QWidget *parent = nullptr);
    ~alarmsWindow();

private:
    Ui::alarmsWindow *ui;
};

#endif // ALARMSWINDOW_H
