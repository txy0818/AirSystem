#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QMainWindow>
#include "airplane.h"

namespace Ui {
class ChangeInfo;
}

class ChangeInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeInfo(QWidget *parent = nullptr);
    ~ChangeInfo();
    void receive(QStringList stringList);
private:
    //private的成员属性或函数调用或修改，需要在公共函数中来使用
    Ui::ChangeInfo *ui;

signals:
    void changeBack(QStringList stringList);
};

#endif // CHANGEINFO_H
