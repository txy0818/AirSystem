#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    user = new UserInterface();
    manager = new ManInterface();
    connect(manager,&ManInterface::back,[=](){
            manager->hide();
            //this->setGeometry(manager->geometry());//这个适用于2个窗口尺寸相同的，不适用不同尺寸的窗口
            this->show();
    });

    connect(user,&UserInterface::back,[=](){
            user->hide();
            //this->setGeometry(user->geometry());
            this->show();
    });


    ui->widget->move(0, this->height()-100);// move 是设置控件的最左上角的在窗体中的位置
    ui->widget->setStyleSheet("background-color: #FFA07A;");// 几乎大多数控件都支持样式表(设置字体，字体大小等)

    ui->widget1->move(0, 0);
    ui->widget1->setStyleSheet("background-color: #FFA07A;");

    ui->widget2->move((this->width() - ui->widget2->width())/2+50 , ui->widget1->height());
    ui->buttonLogin->setStyleSheet("background-color: yellow;");
    ui->buttonQuit->setStyleSheet("background-color: yellow;");

// connect 函数本身并不受槽的访问修饰符（public、protected、private）的限制。
    //这是因为 connect 是一个成员函数，而不是类的成员，因此它可以访问类的私有成员
    connect(ui->buttonLogin, &QPushButton::clicked, this,&MainWindow::clickLogin);
    connect(ui->buttonQuit, &QPushButton::clicked, [=](){
        this->close();
    });

}

//只要窗口移动或缩放都会执行该函数
void MainWindow::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPixmap pix;
    //图片路径   :/.../  资源文件
    pix.load(":/new/image/background.png");//支持大多数格式的图片，比如PNG，JPEG

    //（控件最左上角的x, 控件最左上角的y, 控件的width, 控件的width, 图片）
    painter.drawPixmap(0,ui->widget1->height(),this->width(),this->height()-ui->widget->height(),pix);
}

void MainWindow::clickLogin(){

        QString userType = ui->comboBox->currentText(); // 获取选择的用户类型
        QString filename;

        QString username = ui->lineEditName->text();
        QString password = ui->lineEditPwd->text();

        // 根据用户类型选择对应的文件
        if (userType == "管理员") {
            filename = managerPath;
        } else if (userType == "用户") {
            filename = userPath;
            user->setUsername(username);
        } else {
            qDebug() << "Invalid user type.";
            return;
        }

        ui->lineEditName->clear();
        ui->lineEditPwd->clear();

        // 读取文件中的用户名和密码信息
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open file for reading.";
            return;
        }

        QTextStream in(&file);

        //atEnd() 读到文件尾即为true
        while (!in.atEnd()) {
            QString line = in.readLine();//一行一行读

            //QString::SkipEmptyParts 参数告诉 split() 方法在分割字符串的时候跳过任何空的子字符串
            //这意味着如果有连续的空格或者字符串开始或结尾处有空格时，这些空字符串会被忽略，不会出现在结果的字符串列表中

            //QStringList data = line.split(" "); 若2个非空格的字符串只会跳过他们之间的第一个空格，其他空格每个都作为1个子字符串

            //eg.  1.txt中为txy   txn(2者有3个空格)    line.split(" ");结果:"txy" " " " " "txn"
            //line.split(" ", QString::SkipEmptyParts)结果："txy" "txn"
            //

            QStringList data = line.split(" ", QString::SkipEmptyParts);

            if (data.size() >= 2 && data[0] == username && data[1] == password) {
                qDebug() << "Login successful!";
                this->hide();
                if(userType == "管理员"){
                    manager -> show();
                }
                else{
                    user -> show();
                }

                file.close();
                return;
            }
        }

        QMessageBox::warning(this,"warning","用户名或密码错误");
        file.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

