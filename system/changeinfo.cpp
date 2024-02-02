#include "changeinfo.h"
#include "ui_changeinfo.h"


ChangeInfo::ChangeInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangeInfo)
{
    ui->setupUi(this);

    ui->widget->move(this->width()/2-ui->widget->width()/2, this->height()/2-ui->widget->height()/2);
    ui->widget->setStyleSheet("background-color: lightblue;");
    ui->pushButton->move(this->width()/2-ui->pushButton->width()/2, this->height()-50);
    ui->pushButton->setStyleSheet("background-color: lightblue;");

    connect(ui->pushButton, &QPushButton::clicked,[=](){
        QStringList stringList = {ui->lineEditUser1->text(), ui->lineEditPwd1->text(), ui->lineEditId1->text()};
        this->hide();
        emit changeBack(stringList);
    });

}

void ChangeInfo::receive(QStringList stringList){

    ui->lineEditUser1->setText(stringList[0]);
    ui->lineEditPwd1->setText(stringList[1]);
    ui->lineEditId1->setText(stringList[2]);
}

ChangeInfo::~ChangeInfo()
{
    delete ui;
}
