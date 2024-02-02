#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include "changeinfo.h"
#include "airplane.h"

namespace Ui {
class UserInterface;
}

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:

    explicit UserInterface(QWidget *parent = nullptr);
    ~UserInterface();


    void setUsername(const QString& username);//和mainWindow的传值
    void receiveInfo(QStringList list);//和changeInfo的传值

private:
    ChangeInfo* changeInfo;
    int index = -1;
    QVector<QStringList> stringUser;
    QString username = "";
    Ui::UserInterface *ui;

    void showEvent(QShowEvent *event);
    //订票和退票
    void funcOrder(int row, int column);
    void funcTick(int row, int column);
    void funcTickTotal();

    void createAirWidget(QTableWidget* tableWidget);


signals:
    void back();
};

#endif // USERINTERFACE_H
