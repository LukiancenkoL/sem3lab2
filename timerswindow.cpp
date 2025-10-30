#include "timerswindow.h"
#include "ui_timerswindow.h"

timersWindow::timersWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::timersWindow)
{
    ui->setupUi(this);
}

timersWindow::~timersWindow()
{
    delete ui;
}
