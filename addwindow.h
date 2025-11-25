#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QWidget>
#include <QDialog>
#include <qstringliteral.h>

namespace Ui {
class AddWindow;
}

class AddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWindow(QWidget *parent = nullptr);
    ~AddWindow();
    QString documentPath() const;
    void resetPath();
private slots:
    void createTimerWindow();
    void createAlarmWindow();
    void openFileExplorer();

private:
    Ui::AddWindow *ui{};
    QString m_documentPath{};
};

#endif // ADDWINDOW_H
