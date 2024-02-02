#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maninterface.h"
#include "userinterface.h"
#include "airplane.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void paintEvent(QPaintEvent *event);
    void clickLogin();

    UserInterface* user;
    ManInterface* manager;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
