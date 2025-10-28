#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addwindow.h"

#include <QDialog>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("qrc:/Resources/icon/icon.ico"));


}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::timersMenu()
{
    addWindow menuWindow;
    menuWindow.setModal(true);


}
