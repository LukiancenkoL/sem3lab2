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

    this->ui->doNotDisturb->setChecked(false);

    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(createAddWindow()));

}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::createAddWindow()
{
    addWindow AddWindow;
    AddWindow.setModal(true);

    if (!AddWindow.exec())
    {
        return;
    }


}
