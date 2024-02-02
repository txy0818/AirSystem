#include "userinterface.h"
#include "ui_userinterface.h"

void UserInterface::setUsername(const QString& username) {
    this->username = username;
}

UserInterface::~UserInterface(){
    delete ui;
}

void UserInterface::createAirWidget(QTableWidget* tableWidget){

    //一定要逆序删除行,如果正序删除的话，删除一行，后一行就补充上来了，就没删了这行
    int rowCount = tableWidget->rowCount();

    for (int i = rowCount - 1; i >= 0; --i) {
        tableWidget->removeRow(i);
    }


    QFile file(airplanePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "fail to open the file";
        return;
    }

    QTextStream in(&file);
    int row = 0;

    // 逐行读取文件内容并加载到 QTableWidget 中
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ", QString::SkipEmptyParts);

        // 如果你的 QTableWidget 尚未设置列数和行数，可以根据数据来设置
//        if (tableWidget->columnCount() < fields.size()) {
//            tableWidget->setColumnCount(fields.size());
//        }
        tableWidget->insertRow(row);

        // 将数据逐个添加到 QTableWidget 的单元格中
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[column]);

            QFont font;
            font.setPointSize(12);
            item->setFont(font);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);

            tableWidget->setItem(row, column, item);
        }
        row++;
    }

    file.close(); // 关闭文件
}



UserInterface::UserInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface)
{
    ui->setupUi(this);

    changeInfo = new ChangeInfo();

    ui->tabWidget->setCurrentIndex(0);

    ui->tabWidget->tabBar()->hide();//隐藏tabWidget的表头
    ui->tabWidget->setFixedSize(1340, 810);
    ui->tabWidget->move(0, ui->widget->height() - 5);

    ui->widget->setFixedSize(1340, 150);
    ui->widget->move(0, 0);
    ui->label->setAlignment(Qt::AlignCenter);

    ui->label->setPixmap(QPixmap(":/new/image/nucfont.jpg"));
    ui->label->setScaledContents(true);
//    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setAlignment(Qt::AlignCenter);

    //首页 定退票 修改信息的按钮
    ui->pushButton_1->setStyleSheet("border: none;");
    ui->pushButton_2->setStyleSheet("border: none;");
    ui->pushButton_3->setStyleSheet("border: none;");
    ui->widget->setStyleSheet("background-color: lightblue; color: black; ");

    connect(ui->pushButton_1, &QPushButton::clicked, [=](){
        ui->tabWidget->setCurrentIndex(0);
    });

    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        ui->tabWidget->setCurrentIndex(1);
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [=](){
        ui->tabWidget->setCurrentIndex(2);
    });


    QWidget *tabContent0 = ui->tabWidget->widget(0); //首页

    if (tabContent0) {
        //左图
        QLabel *labelImg1 = tabContent0->findChild<QLabel*>("labelImg1");
        if (labelImg1) {
            labelImg1->move(0, 0);

            labelImg1->setFixedSize(800, 800);
            QPixmap image(":/new/image/userlocation.jpeg"); // 加载图片
            // 设置图片并让其适应标签大小
            labelImg1->setPixmap(image.scaled(labelImg1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // 设置标签大小策略
            labelImg1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            // 允许图片缩放以适应标签
            labelImg1->setScaledContents(true);
        }

        //右图
        QLabel *labelImg2 = tabContent0->findChild<QLabel*>("labelImg2");
        if (labelImg2) {
            labelImg2->move(900, 200);
            labelImg2->setFixedSize(300, 300);

            QPixmap image(":/new/image/person.jpg");
            // 设置图片并让其适应标签大小
            labelImg2->setPixmap(image.scaled(labelImg2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 设置标签大小策略
            labelImg2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            // 允许图片缩放以适应标签
            labelImg2->setScaledContents(true);
        }
        //垂直线
        QFrame* verticalLine = new QFrame(tabContent0);//frame框架
        verticalLine->setFrameShape(QFrame::VLine);//竖垂直线
        verticalLine->setFrameShadow(QFrame::Sunken);
        verticalLine->setGeometry(580, 0, 590, 960);//frame框架的大小
//        verticalLine->setLineWidth(3);//太丑了
        //欢迎文本
        QLineEdit *lineEdit = tabContent0->findChild<QLineEdit*>("lineEdit0");
        if (lineEdit) {
            lineEdit->move(900, 100);
        }
        //退出
        QPushButton *pushButtonQuit = tabContent0->findChild<QPushButton*>("pushButtonQuit0");

        if (pushButtonQuit) {
            pushButtonQuit->setFixedSize(150, 80);
            pushButtonQuit->move(1120, 600);
            pushButtonQuit->setStyleSheet("background-color: lightblue;");

            connect(pushButtonQuit, &QPushButton::clicked, [=](){
                this->close();
            });
        }
        //返回
        QPushButton *pushButtonBack = tabContent0->findChild<QPushButton*>("pushButtonBack0");

        if (pushButtonBack) {
            pushButtonBack->setFixedSize(150, 80);
            pushButtonBack->move(1120, 710);
            pushButtonBack->setStyleSheet("background-color: lightblue;");

            connect(pushButtonBack, &QPushButton::clicked, [=](){
                emit back();
            });
        }
    }

    QWidget *tabContent1 = ui->tabWidget->widget(1); //订，退票

    if (tabContent1) {
        //背景图
        QLabel *label = tabContent1->findChild<QLabel*>("labelImg");

        if (label) {

            label->move(0, 0);
            label->setFixedSize(1340, 960);

            QPixmap image(":/new/image/userman.jpg");
            // 设置图片并让其适应标签大小
            label->setPixmap(image.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 设置标签大小策略
//            label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            // 允许图片缩放以适应标签
            label->setScaledContents(true);

            label->lower();
        }
        //退出
        QPushButton *pushButtonQuit = tabContent1->findChild<QPushButton*>("pushButtonQuit1");

        if (pushButtonQuit) {
            pushButtonQuit->setFixedSize(150, 80);
            pushButtonQuit->move(1120, 600);
            pushButtonQuit->setStyleSheet("background-color: lightblue;");

            connect(pushButtonQuit, &QPushButton::clicked, [=](){
                this->close();
            });
        }
        //返回
        QPushButton *pushButtonBack = tabContent1->findChild<QPushButton*>("pushButtonBack1");
        if (pushButtonBack) {
            pushButtonBack->setFixedSize(150,80);
            pushButtonBack->move(1120,710);
            pushButtonBack->setStyleSheet("background-color: lightblue;");

            connect(pushButtonBack, &QPushButton::clicked, [=](){
                emit back();
            });
        }

        QTableWidget *tableWidget = tabContent1->findChild<QTableWidget*>("tableWidget");

        if (tableWidget) {

            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            tableWidget->setStyleSheet("QTableWidget { background-color: lightblue; }");
            tableWidget->move(20, 20);

            createAirWidget(tableWidget);
            //下拉框
            QComboBox *comboBox = tabContent1->findChild<QComboBox*>("comboBox");
            if (comboBox) {
                comboBox->move(50, 700);
            }
            //待输文本
            QLineEdit* lineEditSeek = tabContent1->findChild<QLineEdit*>("lineEditSeek");
            if (lineEditSeek) {
                lineEditSeek->move(150, 700);
            }
            //退票
            QPushButton *pushButtonTick = tabContent1->findChild<QPushButton*>("pushButtonTick");
            if (pushButtonTick) {
                pushButtonTick->setEnabled(false);
                pushButtonTick->move(600,700);
                pushButtonTick->setStyleSheet("background-color: lightblue;");
            }
            //退票的确认按钮
            QPushButton *pushButtonTick1 = tabContent1->findChild<QPushButton*>("pushButtonTick1");

            if (pushButtonTick1) {

                pushButtonTick1->move(700,700);
                pushButtonTick1->setStyleSheet("background-color: lightblue;");

                connect(pushButtonTick1, &QPushButton::clicked, [=](){
                    disconnect(tableWidget, &QTableWidget::cellClicked, this, &UserInterface::funcTick);
                });
            }


        //下拉框的确认按钮
        QPushButton *pushButtonInfo = tabContent1->findChild<QPushButton*>("pushButtonInfo");
        if (pushButtonInfo) {

            pushButtonInfo->move(250, 700);
            pushButtonInfo->setStyleSheet("background-color: lightblue;");

            connect(pushButtonInfo, &QPushButton::clicked, [=](){

                QString selectedType = comboBox->currentText();
                int index = comboBox->currentIndex();
                QString newData = lineEditSeek->text();
                lineEditSeek->clear();

                QStringList userAir;
                if(selectedType == "我的" && newData == ""){

                    QFile file(userPath);
                    if (!file.open(QIODevice::ReadOnly)) {
                        qDebug() << "fail to open the file";
                        return;
                    }
                    QTextStream in(&file);

                    while (!in.atEnd()) {

                        QString line = in.readLine();
                        QStringList stringList = line.split(" ", QString::SkipEmptyParts);
                        if(stringList[0] == username){
                            if(stringList[3] == "否"){
                                QMessageBox::warning(this, "未预订", "请先预订");
                                return;
                            }
                            for(int j = 4; j <= 8; j++){
                                if(stringList[j] != "0"){
                                    userAir.append(stringList[j]);
                                }

                            }
                        }

                    }

                    file.close();

                    // 从最后一行开始逐行删除
                    for (int i = tableWidget->rowCount() - 1; i >= 0; --i) {
                        tableWidget->removeRow(i);
                    }

                    QFile file1(airplanePath);
                    if (!file1.open(QIODevice::ReadOnly)) {
                        qDebug() << "fail to open the file";
                        return;
                    }
                    QTextStream in1(&file1);
                    int row = 0;
                    while (!in1.atEnd()) {

                        QString line = in1.readLine();
                        QStringList stringList = line.split(" ", QString::SkipEmptyParts);
                        for(int i = 0; i < userAir.count(); i++){
                            if(userAir[i] == stringList[0]){

                                tableWidget->insertRow(row);
                                for (int column = 0; column < tableWidget->columnCount(); ++column) {
                                    QTableWidgetItem *item = new QTableWidgetItem(stringList[column]);

                                    QFont font;
                                    font.setPointSize(12);
                                    item->setFont(font);
                                    item->setTextAlignment(Qt::AlignCenter);
                                    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

                                    tableWidget->setItem(row, column, item);
                                }
                                row++;
                            }

                        }
                    }

                    pushButtonTick->setEnabled(true);
                    connect(pushButtonTick, &QPushButton::clicked, this,&UserInterface::funcTickTotal);
                    file1.close();
                    return;
                }
                else if(selectedType == "我的" && newData != ""){
                    pushButtonTick->setEnabled(false);
//                    disconnect(pushButtonTick, &QPushButton::clicked, this,&UserInterface::funcTickTotal);
                    QMessageBox::warning(this, "未按格式", "请重试");
                    return;
                }
                else{
                    pushButtonTick->setEnabled(false);
//                    disconnect(pushButtonTick, &QPushButton::clicked, this,&UserInterface::funcTickTotal);
                    // 从最后一行开始逐行删除
                    for (int i = tableWidget->rowCount() - 1; i >= 0; --i) {
                        tableWidget->removeRow(i);
                    }

                    QFile file(airplanePath);
                    if (!file.open(QIODevice::ReadOnly)) {
                        qDebug() << "fail to open the file";
                        return;
                    }
                    QTextStream in(&file);
                    int row = 0;
                    while (!in.atEnd()) {

                        QString line = in.readLine();
                        QStringList stringList = line.split(" ", QString::SkipEmptyParts);
                        if(stringList[index] == newData){

                            if (tableWidget->columnCount() < stringList.size()) {
                                tableWidget->setColumnCount(stringList.size());
                            }
                            tableWidget->insertRow(row);

                            for (int column = 0; column < tableWidget->columnCount(); ++column) {
                                QTableWidgetItem *item = new QTableWidgetItem(stringList[column]);

                                QFont font;
                                font.setPointSize(12);
                                item->setFont(font);
                                item->setTextAlignment(Qt::AlignCenter);
                                item->setFlags(item->flags() ^ Qt::ItemIsEditable);

                                tableWidget->setItem(row, column, item);
                            }
                            row++;
                        }
                    }

                    if(row == 0){
                        QMessageBox::warning(this, "无该值", "请重试");
                    }
                    file.close();

                }

            });
        }
        //恢复全部
        QPushButton *pushButtonRecover = tabContent1->findChild<QPushButton*>("pushButtonRecover");
        if (pushButtonRecover) {

            pushButtonRecover->move(350, 700);
            pushButtonRecover->setStyleSheet("background-color: lightblue;");

            connect(pushButtonRecover, &QPushButton::clicked, [=](){
                pushButtonTick->setEnabled(false);
//                disconnect(pushButtonTick, &QPushButton::clicked, this,&UserInterface::funcTickTotal);
                createAirWidget(tableWidget);
            });
        }
        //订票
        QPushButton *pushButtonOrder = tabContent1->findChild<QPushButton*>("pushButtonOrder");

        if (pushButtonOrder) {

            pushButtonOrder->move(600, 630);
            pushButtonOrder->setStyleSheet("background-color: lightblue;");

            connect(pushButtonOrder, &QPushButton::clicked, [=](){
                connect(tableWidget, &QTableWidget::cellClicked, this, &UserInterface::funcOrder);
            });
        }
        //订票的确认按钮
        QPushButton *pushButtonOrder1 = tabContent1->findChild<QPushButton*>("pushButtonOrder1");

        if (pushButtonOrder1) {

            pushButtonOrder1->move(700,630);
            pushButtonOrder1->setStyleSheet("background-color: lightblue;");

            connect(pushButtonOrder1, &QPushButton::clicked, [=](){
                tableWidget->clearSelection();
                //为什么可以写局部变量，而我写int index的局部变量就不行，因为tableWidget是指针，作用域大况且他还在类的构造函数中，随类的释放才释放
                //你把index写到一个类的成员函数中，他的作用域很小，connect只要连接上，就能用，也就是说你的index还没在connect中使用，index可能已经
                //被释放了
                disconnect(tableWidget, &QTableWidget::cellClicked, this, &UserInterface::funcOrder);
            });
        }
      }
    }

    QWidget *tabContent2 = ui->tabWidget->widget(2); //用户信息

    if (tabContent2) {

        QWidget *widget_2 = tabContent2->findChild<QWidget*>("widgetChange");

        if (widget_2) {

            widget_2->move(1340/2 - 300, 20);
            widget_2->setStyleSheet("background-color: lightblue;");

        }

        //背景图
        QLabel *label = tabContent2->findChild<QLabel*>("label2");

        if (label) {

            label->move(0, 0);
            label->setFixedSize(1340,960);

            QPixmap image(":/new/image/userman.jpg"); // 加载图片

            // 设置图片并让其适应标签大小
            label->setPixmap(image.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 设置标签大小策略
//            label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            // 允许图片缩放以适应标签
            label->setScaledContents(true);

            label->lower();
        }


        //退出
        QPushButton *pushButtonQuit = tabContent2->findChild<QPushButton*>("pushButtonQuit3");
        if (pushButtonQuit) {

            connect(pushButtonQuit, &QPushButton::clicked, [=](){
                this->close();
            });
        }

        //返回
        QPushButton *pushButtonBack = tabContent2->findChild<QPushButton*>("pushButtonBack3");

        if (pushButtonBack) {
            connect(pushButtonBack, &QPushButton::clicked, [=](){
                emit back();
            });
        }

    }

}

//订票,点击航班号进行订票
void UserInterface::funcOrder(int row, int column){


    QWidget *tabContent1 = ui->tabWidget->widget(1);

    if (tabContent1) {
        QTableWidget *tableWidget = tabContent1->findChild<QTableWidget*>("tableWidget");

        if (tableWidget) {

            if(column == 0){
                    QTableWidgetItem* item = tableWidget->item(row, column);
                    QTableWidgetItem* item1 = tableWidget->item(row, column + 9);

                    if (item1->text().toInt() > 0) {

                        QVector<QStringList> stringAir;
                        QVector<QStringList> stringUser;


                        QFile file(airplanePath);
                        if (!file.open(QIODevice::ReadOnly)) {
                            qDebug() << "fail to open the file";
                            return;
                        }

                        QTextStream in(&file);

                        while (!in.atEnd()) {
                            QString line = in.readLine();
                            QStringList fields = line.split(" ", QString::SkipEmptyParts);
                            stringAir.append(fields);
                        }
                        file.close();


                        QFile file1(userPath);
                        if (!file1.open(QIODevice::ReadOnly)) {
                            qDebug() << "fail to open the file";
                            return;
                        }

                        QTextStream in1(&file1);

                        while (!in1.atEnd()) {
                            QString line = in1.readLine();
                            QStringList fields = line.split(" ", QString::SkipEmptyParts);
                            stringUser.append(fields);
                        }
                        file1.close();


                        for(int i = 0; i < stringUser.size(); i++){
                            if(stringUser[i][0] == this->username){
                                int j = 4;
                                for(; j <= 8 && stringUser[i][j] != "0"; j++){
                                    if(stringUser[i][j] == item->text()){
                                        QMessageBox::information(this, "已经预订", "一趟航班一人一票");
                                        return;
                                    }

                                }

                                if(j > 8){
                                    QMessageBox::information(this, "已经预订", "5张票已满");
                                }
                                else{
                                    stringUser[i][j] = item->text();

                                    int number = item1->text().toInt() - 1;

                                    item1->setText(QString::number(number));

                                    for(int i = 0; i < stringAir.size(); i++){
                                        if(stringAir[i][0] == item->text()){
                                            stringAir[i][9] = QString::number(number);
                                        }
                                    }

                                    QFile file(airplanePath);
                                    if (!file.open(QIODevice::WriteOnly)) {
                                        qDebug() << "fail to open the file";
                                        return;
                                    }

                                    QTextStream out(&file);
                                    for(int i = 0; i < stringAir.size(); i++) {
                                       int j = stringAir[0].count();
                                       for(int k = 0; k < j; k++){
                                           out << stringAir[i][k] << " ";
                                       }
                                       out << "\n";
                                    }

                                    file.close();

                                    QFile file1(userPath);
                                    if (!file1.open(QIODevice::WriteOnly)) {
                                        qDebug() << "fail to open the file";
                                        return;
                                    }

                                    // 读取文件内容
                                    QTextStream out1(&file1);
                                    for(int i = 0; i < stringUser.size(); i++) {
                                       int j = stringUser[0].count();
                                       for(int k = 0; k < j; k++){
                                           out1 << stringUser[i][k] << " ";
                                       }
                                       out1 << "\n";
                                    }

                                    file1.close();
                                    QMessageBox::information(this, "预订成功", "成功预订");
                                }
                            }
                        }
                        return;
                    }
                    else{
                        QMessageBox::warning(this, "已经满员", "无票");
                    }
                }
            }
        }
}

//退票

//退票按钮实现可以按单元格进行操作
void UserInterface::funcTickTotal(){

    QWidget *tabContent1 = ui->tabWidget->widget(1);

    if (tabContent1) {
        QTableWidget *tableWidget = tabContent1->findChild<QTableWidget*>("tableWidget");
        if (tableWidget) {
            connect(tableWidget, &QTableWidget::cellClicked, this, &UserInterface::funcTick);
        }
    }

}

//按单元格和退票实现进行连接，点击确定将按单元格和退票断开，点击恢复全部或查询其他都会断开退票按钮实现可以按单元格进行操作
void UserInterface::funcTick(int row, int column){

    QWidget *tabContent1 = ui->tabWidget->widget(1);

    if (tabContent1) {
        QTableWidget *tableWidget = tabContent1->findChild<QTableWidget*>("tableWidget");

        if (tableWidget) {

            if(column == 0){

                QVector<QStringList> stringAir;
                QVector<QStringList> stringUser;

                QFile file(airplanePath);
                if (!file.open(QIODevice::ReadOnly)) {
                    // 文件打开失败，处理错误
                    qDebug() << "fail to open the file";
                    return;
                }

                QTextStream in(&file);

                while (!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList fields = line.split(" ", QString::SkipEmptyParts);
                    stringAir.append(fields);

                }
                file.close();


                QFile file1(userPath);
                if (!file1.open(QIODevice::ReadOnly)) {
                    // 文件打开失败，处理错误
                    qDebug() << "fail to open the file";
                    return;
                }

                // 读取文件内容
                QTextStream in1(&file1);
                while (!in1.atEnd()) {
                    QString line = in1.readLine();
                    QStringList fields = line.split(" ", QString::SkipEmptyParts);
                    stringUser.append(fields);
                }
                file1.close();

                QTableWidgetItem* item = tableWidget->item(row, column);

                for(int i = 0; i < stringAir.size(); i++){
                    if(item->text() == stringAir[i][0]){
                        stringAir[i][9] = QString::number((stringAir[i][9].toInt()) + 1);
                        break;
                    }
                }

                QStringList userAir;
                for(int i = 0; i < stringUser.size(); i++){
                    if(username == stringUser[i][0]){
                        for(int j = 4; j <=8; j++){
                            if(stringUser[i][j] == item->text()){
                                for(int k = j; k <8; k++){
                                    stringUser[i][k] = stringUser[i][k+1];
                                }
                                stringUser[i][8] = "0";
                            }
                        }

                        for(int j = 4; j <= 8 && stringUser[i][j] != "0"; j++){
                            userAir.append(stringUser[i][j]);
                        }

                    }
                }

                QFile file2(airplanePath);
                if (!file2.open(QIODevice::WriteOnly)) {
                    qDebug() << "fail to open the file";
                    return;
                }

                QTextStream out2(&file2);

                for(int i = 0; i < stringAir.size(); i++) {
                   int j = stringAir[0].count();
                   for(int k = 0; k < j; k++){
                       out2 << stringAir[i][k] << " ";
                   }
                   out2 << "\n";
                }

                file2.close();

                QFile file3(userPath);
                if (!file3.open(QIODevice::WriteOnly)) {
                    qDebug() << "fail to open the file";
                    return;
                }

                QTextStream out3(&file3);

                for(int i = 0; i < stringUser.size(); i++) {
                   int j = stringUser[0].count();
                   for(int k = 0; k < j; k++){
                       out3 << stringUser[i][k] << " ";
                   }
                   out3 << "\n";
                }

                file3.close();

                for (int i = tableWidget->rowCount() - 1; i >= 0; --i) {
                    tableWidget->removeRow(i);
                }

                QFile file4(airplanePath);
                if (!file4.open(QIODevice::ReadOnly)) {
                    qDebug() << "fail to open the file";
                    return;
                }
                QTextStream in4(&file4);
                int row = 0;
                while (!in4.atEnd()) {

                    QString line = in4.readLine();
                    QStringList stringList = line.split(" ", QString::SkipEmptyParts);
                    for(int i = 0; i < userAir.count(); i++){
                        if(userAir[i] == stringList[0]){

                            tableWidget->insertRow(row);

                            for (int column = 0; column < tableWidget->columnCount(); ++column) {
                                QTableWidgetItem *item = new QTableWidgetItem(stringList[column]);

                                QFont font;
                                font.setPointSize(12);
                                item->setFont(font);
                                item->setTextAlignment(Qt::AlignCenter);
                                item->setFlags(item->flags() ^ Qt::ItemIsEditable);

                                tableWidget->setItem(row, column, item);
                            }
                            row++;
                        }


                    }

                }

            }
        }
    }
}

//调用 QWidget show()显示窗口或隐藏该窗口hide()时，showEvent 函数就会被触发
void UserInterface::showEvent(QShowEvent *event) {
    // 首先调用基类的 showEvent
    QWidget::showEvent(event);

    stringUser.clear();

    QWidget *tabContent2 = ui->tabWidget->widget(2);

    if (tabContent2) {

            QStringList userInfo;

            QFile file1(userPath);
            if (!file1.open(QIODevice::ReadOnly)) {
                qDebug() << "fail to open the file";
                return;
            }

            QTextStream in1(&file1);

            int j = 0;
            while (!in1.atEnd()) {
                QString line = in1.readLine();
                QStringList fields = line.split(" ", QString::SkipEmptyParts);
                stringUser.append(fields);
                if(username == fields[0]){
                    index = j;
                    for(int i = 0; i < fields.count() && fields[i] != "0"; i++){
                        userInfo.append(fields[i]);
                    }
                }
                j++;

            }
            file1.close();

            QLineEdit *lineEditUser1 = tabContent2->findChild<QLineEdit*>("lineEditUser1");

            if (lineEditUser1) {

               lineEditUser1->setReadOnly(false);
               lineEditUser1->setText(username);
               lineEditUser1->setReadOnly(true);
            }

            QLineEdit *lineEditPwd1 = tabContent2->findChild<QLineEdit*>("lineEditPwd1");

            if (lineEditPwd1) {
                lineEditPwd1->setReadOnly(false);
                lineEditPwd1->setText(userInfo[1]);
                lineEditPwd1->setReadOnly(true);

            }

            QLineEdit *lineEditId1 = tabContent2->findChild<QLineEdit*>("lineEditId1");
            if (lineEditId1) {
                lineEditId1->setReadOnly(false);
                lineEditId1->setText(userInfo[2]);
                lineEditId1->setReadOnly(true);
            }
            //  修改
            QPushButton *pushButtonChange = tabContent2->findChild<QPushButton*>("pushButtonChange");

            if (pushButtonChange) {
                connect(pushButtonChange, &QPushButton::clicked, [=](){
                    QStringList list ={userInfo[0], userInfo[1], userInfo[2]};
                    this->hide();
                    changeInfo->show();
                    changeInfo->receive(list);
                });
            }

            //这个连接的启发：我原来使用的index，stringUser是这个函数中的局部变量,这个存在连接时局部变量的作用
            //域导致的问题，[&](){}导致index,stringUser不能正确传入
            //对于在connect中想要修改的变量 [=](){}  写成该类的成员属性，或ui中创建的控件也可，其他的都不行
            connect(changeInfo, &ChangeInfo::changeBack,[=](QStringList stringList){

                    ui->lineEditUser1->setReadOnly(false);
                    ui->lineEditUser1->setText(stringList[0]);
                    ui->lineEditUser1->setReadOnly(true);

                    ui->lineEditPwd1->setReadOnly(false);
                    ui->lineEditPwd1->setText(stringList[1]);
                    ui->lineEditPwd1->setReadOnly(true);

                    ui->lineEditId1->setReadOnly(false);
                    ui->lineEditId1->setText(stringList[2]);
                    ui->lineEditId1->setReadOnly(true);

                    stringUser[index][0] = stringList[0];
                    stringUser[index][1] = stringList[1];
                    stringUser[index][2] = stringList[2];

                    QFile file3(userPath);
                    if (!file3.open(QIODevice::WriteOnly)) {
                        // 文件打开失败，处理错误
                        qDebug() << "fail to open the file";
                        return;
                    }

                    QTextStream out3(&file3);
                    for(int i = 0; i < stringUser.size(); i++) {
                       int j = stringUser[0].count();
                       for(int k = 0; k < j; k++){
                           out3 << stringUser[i][k] << " ";
                       }
                       out3 << "\n";
                    }
                    file3.close();
                    this->show();
            });
        }

}
