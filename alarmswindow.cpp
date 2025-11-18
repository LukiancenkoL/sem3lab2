#include "alarmswindow.h"
#include "ui_alarmswindow.h"

alarmsWindow::alarmsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::alarmsWindow)
{
    ui->setupUi(this);
}

alarmsWindow::~alarmsWindow()
{
    delete ui;
}
