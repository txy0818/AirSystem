#include "maninterface.h"
#include "ui_maninterface.h"

void ManInterface::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/image/nucfont.jpg");
    pix = pix.scaled(pix.width() / 2, pix.height());//对图像进行缩放
    painter.drawPixmap(0,0,pix.width()*2.7,80,pix);

}


void ManInterface::createUserWidget(QTableWidget* tableWidget){

    QFile file(userPath);
    if (!file.open(QIODevice::ReadOnly)) {
        // 文件打开失败，处理错误
        qDebug() << "fail to open the file";
        return;
    }

    // 读取文件内容
    QTextStream in(&file);
    int row = 0;

    // 逐行读取文件内容并加载到 QTableWidget 中
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(QChar::Space, QString::SkipEmptyParts);

        // 如果你的 QTableWidget 尚未设置列数和行数，可以根据数据来设置,必须设置，否则实现不了
        //像是在ui界面设置了列，如首页，管理等这种就是设置了列数
//        if (tableWidget->columnCount() < fields.size()) {
//            tableWidget->setColumnCount(fields.size());
//        }
        tableWidget->insertRow(row);
        // 将数据逐个添加到 QTableWidget 的单元格中
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = nullptr;
            if(column >= 4 && fields[column] == "0"){
                item = new QTableWidgetItem("");
            }
            else{
                item = new QTableWidgetItem(fields[column]);
            }
            QFont font;
            font.setPointSize(20);
            item->setFont(font);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);//取消该 QTableWidgetItem 的可编辑性

            tableWidget->setItem(row, column, item);
        }
        row++;
    }

    file.close(); // 关闭文件
}


void ManInterface::createAirWidget(QTableWidget* tableWidget){

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
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);

            tableWidget->setItem(row, column, item);
        }
        row++;
    }

    file.close(); // 关闭文件
}


bool compare(const QStringList& a, const QStringList& b){
    return a[0] < b[0];
}

void ManInterface::sort(QVector<QStringList>& vectorAll, QVector<QStringList> vector){

    QVector<QStringList> copy;
    int count = 0;
    for(auto& i : vectorAll){
        QStringList list = i;
        list.append(QString::number(count));
        count++;
        copy.append(list);
    }

    qSort(copy.begin(), copy.end(), compare);

    for(int i = 0; i < vector.size(); i++){
        int low = 0;
        int high = copy.size() - 1;
        for(; low <= high;){
            int mid = (low + high) / 2;
            if(vector[i][0] > copy[mid][0]){
                low = mid + 1;
            }
            else if(vector[i][0] < copy[mid][0]){
                high = mid - 1;
            }
            else{
                vectorAll[copy[mid][10].toInt()] = vector[i];
                break;
            }
        }

    }

}

void ManInterface::flushAirFile(QVector<QStringList> vector){

    QVector<QStringList> vectorAll;
    QFile file(airplanePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "fail to open the file";
        return;
    }

    QTextStream in(&file);

    // 逐行读取文件内容并加载到 QTableWidget 中
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ", QString::SkipEmptyParts);
        vectorAll.append(fields);
    }
    file.close();

    sort(vectorAll, vector);

//    for(int i = 0; i < vectorAll.size(); i++){
//        for(int j = 0; j < vector.size(); j++){
//            if(vectorAll[i][0] == vector[j][0]){
//                vectorAll[i] = vector[j];
//                break;
//            }
//        }
//    }

    QFile file1(airplanePath);
    if (!file1.open(QIODevice::WriteOnly)) {
        qDebug() << "fail to open the file";
        return;
    }

   QTextStream out(&file1);
   for (int i = 0; i < vectorAll.size(); ++i) {
       for (int j = 0; j < vectorAll[0].count(); ++j) {
          out << vectorAll[i][j] << " ";
       }
       out<<"\n";
   }
    file1.close();
}

void ManInterface::flushUserFile(QTableWidget *tableWidget){

    QFile file(userPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "fail to open the file";
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (col < 4) {
                out << item->text() << " ";
            }
            else if(col >= 4 && item->text() == ""){
                out << "0" << " ";
            }
            else if(col >= 4 && item->text() != ""){
                out << item->text() << " ";
            }


        }
        out << "\n";
    }

    file.close();
}



ManInterface::ManInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManInterface)
{
    ui->setupUi(this);

    ui->tabWidget->move(0,0);
    ui->tabWidget->resize(this->size());
    ui->tabWidget->setStyleSheet("QTabBar::tab { background-color: lightblue; }");

    QWidget *tabContent3 = ui->tabWidget->widget(3); //索引为3的选项卡   首页
    ui->tabWidget->setCurrentIndex(3);

    //查找是否存在该控件，也可以直接用ui->tab3即可
    if (tabContent3) {

        // 使用控件的名称或对象名称查找控件,若未找到，返回nullptr,也可以直接用ui->label即可
        //左侧图片
        QLabel *label = tabContent3->findChild<QLabel*>("label3");

        if (label) {
            label->move(20, 20);
            label->setFixedSize(tabContent3->width()/2, tabContent3->height());

            QPixmap image(":/new/image/airport.jpg");

            // 设置图片并让其适应标签大小
            //Qt::KeepAspectRatio 是用于指定图像在调整大小时保持纵横比
            //Qt::SmoothTransformation 是指在图像缩放过程中使用平滑的转换方法，以产生更平滑和清晰的图像
            label->setPixmap(image.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 设置标签大小策略        

//            在 Qt 中，父级布局指的是控件的直接父控件所使用的布局管理器。例如，如果将一个 QLabel 放置在 QWidget 上，并且 QWidget 使用了布局管理器（例如 QVBoxLayout、QHBoxLayout 等），
//            那么这个 QWidget 就是 QLabel 的父控件，并且 QLabel 的大小可能受到 QWidget 所使用的布局管理器的影响。

//            通过设置控件的大小策略为 QSizePolicy::Ignored，控件会忽略其直接父控件使用的布局管理器对其大小的调整。
//            这意味着即使父控件使用了布局管理器，控件也会尽量保持其原始的大小，而不会被布局管理器所调整
            //label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);//忽略其父级布局对其大小的调整，我没有使用父级布局法

            // 允许图片缩放以适应标签
            label->setScaledContents(true);
        }

        //也可以在ui界面直接布局（用widget）

        //以下全是位置布局
        //欢迎的文本
        QLineEdit *lineEdit = tabContent3->findChild<QLineEdit*>("lineEdit");

        if (lineEdit) {
            lineEdit->setFixedSize(300, 40);
            lineEdit->move(tabContent3->width()/2 + 50, 50);
        }

        //发公告的文本
        QLineEdit *lineEditAnnounce = tabContent3->findChild<QLineEdit*>("lineEditAnnounce");

        if (lineEditAnnounce) {
            lineEditAnnounce->move(tabContent3->width()/2 + 50, 100);
            lineEditAnnounce->setStyleSheet("color: blue");
        }

        //退出按钮
        QPushButton *pushButtonQuit3 = tabContent3->findChild<QPushButton*>("pushButtonQuit3");

        if (pushButtonQuit3) {
            pushButtonQuit3->setFixedSize(150,80);
            pushButtonQuit3->move(tabContent3->width()/2 + 390, tabContent3->height()-200);
            pushButtonQuit3->setStyleSheet("background-color: lightblue;");

            connect(pushButtonQuit3, &QPushButton::clicked, [=](){
                this->close();
            });
        }

        //返回按钮
        QPushButton *pushButtonBack3 = tabContent3->findChild<QPushButton*>("pushButtonBack3");
        if (pushButtonBack3) {
            pushButtonBack3->setFixedSize(150,80);
            pushButtonBack3->move(tabContent3->width()/2 + 390,
                             tabContent3->height()-300);
            pushButtonBack3->setStyleSheet("background-color: lightblue;");

            connect(pushButtonBack3, &QPushButton::clicked, [=](){
                emit back();
            });
        }

        //公告栏
        QTextEdit *textEdit = tabContent3->findChild<QTextEdit*>("textEdit");

        if (textEdit) {
            textEdit->setFixedSize(400, 300);
            textEdit->move(tabContent3->width()/2 + 50, 210);

            QFile file(announcePath);
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << "fail to open the file";
                return;
            }

            QTextStream in(&file);

            while (!in.atEnd()) {
                QString line = in.readLine();
                textEdit->append(line);//QTextEdit::append()函数用于将文本追加到QTextEdit小部件的末尾,会在line后面加上"\n"
            }

            file.close();

        }

        //发公告的文本框
        QLineEdit *lineEditPut = tabContent3->findChild<QLineEdit*>("lineEditPut");
        if (lineEditPut) {
            lineEditPut->setFixedSize(300, 80);
            lineEditPut->move(tabContent3->width()/2 + 50, 550);
        }
        //发公告按钮
        QPushButton *pushButtonPut = tabContent3->findChild<QPushButton*>("pushButtonPut");

        if (pushButtonPut) {
            pushButtonPut->setFixedSize(150,80);
            pushButtonPut->move(tabContent3->width()/2 + 390, 550);
            pushButtonPut->setStyleSheet("background-color: lightblue;");

            connect(pushButtonPut, &QPushButton::clicked, [=](){
                QString string = lineEditPut->text();
                lineEditPut->clear();

                if(string == ""){
                    QMessageBox::warning(this, "无文本输入", "不能实现");
                    return;
                }
                textEdit->setReadOnly(false);
                textEdit->append(string);
                textEdit->setReadOnly(true);

                QFile file(announcePath);
                if (!file.open(QIODevice::WriteOnly)) {
                    qDebug() << "fail to open the file";
                    return;
                }

                QTextDocument *document = textEdit->document(); // 获取 QTextEdit 的文档对象

                QTextStream out(&file);

                for (QTextBlock block = document->begin(); block != document->end(); block = block.next()) {
                    out << block.text() << "\n";
                }

                file.close(); // 关闭文件
            });
        }

    }


    QWidget *tabContent2 = ui->tabWidget->widget(2);// 航班管理

    if (tabContent2) {
        //背景图
        QLabel *label2 = tabContent2->findChild<QLabel*>("label2");

        if (label2) {

            label2->move(0, 0);
            label2->setFixedSize(tabContent2->width(), tabContent2->height());

            QPixmap image(":/new/image/adminman.jpg");

            // 设置图片并让其适应标签大小
            label2->setPixmap(image.scaled(label2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 设置标签大小策略
//            label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            // 允许图片缩放以适应标签
            label2->setScaledContents(true);

            label2->lower();//放到所有控件的最下层
        }
        //返回
        QPushButton *pushButtonBack2 = tabContent2->findChild<QPushButton*>("pushButtonBack2");

        if (pushButtonBack2) {
            pushButtonBack2->setFixedSize(150,80);
            pushButtonBack2->move(tabContent2->width()-300, tabContent2->height()-300);
            pushButtonBack2->setStyleSheet("background-color: lightblue;");

            connect(pushButtonBack2, &QPushButton::clicked, [=](){
                emit back();
            });
        }
        //退出
        QPushButton *pushButtonQuit2 = tabContent2->findChild<QPushButton*>("pushButtonQuit2");
        if (pushButtonQuit2) {
            pushButtonQuit2->setFixedSize(150,80);
            pushButtonQuit2->move(tabContent2->width()-300, tabContent2->height()-200);
            pushButtonQuit2->setStyleSheet("background-color: lightblue;");

            connect(pushButtonQuit2, &QPushButton::clicked, [=](){
                this->close();
            });
        }
        //表格
        QTableWidget *tableWidgetAir = tabContent2->findChild<QTableWidget*>("tableWidgetAir");

        if (tableWidgetAir) {

            tableWidgetAir->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//列的大小将保持固定，不能被拉伸或调整
            tableWidgetAir->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//行的大小将保持固定，不能被拉伸或调整
            tableWidgetAir->setStyleSheet("QTableWidget { background-color: lightblue; }");

            tableWidgetAir->move(20, 20);

            createAirWidget(tableWidgetAir);
            //修改
            QPushButton *pushButtonchange = tabContent2->findChild<QPushButton*>("pushButtonChange");
            if (pushButtonchange) {

                pushButtonchange->move(50, tabContent2->height()-200);
                pushButtonchange->setStyleSheet("background-color: lightblue;");

                connect(pushButtonchange, &QPushButton::clicked, [=](){

                    for (int row = 0; row < tableWidgetAir->rowCount(); ++row) {
                        for (int col = 1; col < tableWidgetAir->columnCount(); ++col) {
                            QTableWidgetItem *item = tableWidgetAir->item(row, col);
                            if (item) {
                                item->setFlags(item->flags() | Qt::ItemIsEditable); // 设置为可编辑
                            }
                        }
                    }
                });
            }
            //修改的确认按钮
            QPushButton *pushButtonRight = tabContent2->findChild<QPushButton*>("pushButtonRight");
            if (pushButtonRight) {
                tableWidgetAir->clearSelection();

                pushButtonRight->move(150, tabContent2->height()-200);
                pushButtonRight->setStyleSheet("background-color: lightblue;");

                connect(pushButtonRight, &QPushButton::clicked, [=](){
                    tableWidgetAir->clearSelection();
                    QStringList stringList;
                    QVector<QStringList> vector;
                    int col = 0;
                    for (int row = 0; row < tableWidgetAir->rowCount(); ++row) {
                        QTableWidgetItem *item = tableWidgetAir->item(row, col);
                        stringList.append(item->text());
                    }

                    for (int row = 0; row < tableWidgetAir->rowCount(); ++row) {
                        QStringList data;
                        for (int col = 0; col < tableWidgetAir->columnCount(); ++col) {
                            QTableWidgetItem *item = tableWidgetAir->item(row, col);
                            data.append(item->text());
                            if (item) {
                                item->setFlags(item->flags() & ~Qt::ItemIsEditable);// 设置为不可编辑
                            }

                            if ((item && item->text() =="")||(col == 8 && item->text() == "0")) {
                                if(item && item->text() ==""){
                                    QMessageBox::warning(this, "修改为空", "不能实现");
                                }
                                else{
                                    QMessageBox::warning(this, "座位数不能为0", "不能实现");
                                }

                                //一定要逆序删除行,如果正序删除的话，删除一行，后一行就补充上来了，就没删了这行
                                int rowCount = tableWidgetAir->rowCount();

                                for (int i = rowCount - 1; i >= 0; --i) {
                                    tableWidgetAir->removeRow(i);
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

                                    tableWidgetAir->insertRow(row);

                                    for(int i = 0; i < stringList.count(); i++){
                                        if(stringList[i] == fields[0]){
                                            for (int column = 0; column < tableWidgetAir->columnCount(); ++column) {
                                                QTableWidgetItem *item = new QTableWidgetItem(fields[column]);
                                                QFont font;
                                                font.setPointSize(12);
                                                item->setFont(font);
                                                item->setTextAlignment(Qt::AlignCenter);
                                                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                                                tableWidgetAir->setItem(row, column, item);
                                            }
                                            row++;
                                            break;
                                        }
                                    }
                                }

                                file.close(); // 关闭文件
                                return;
                            }
                        }
                         vector.append(data);//QVector的count和size都是元素个数  QStringList的元素个数是count()
                    }

                    flushAirFile(vector);

                });

            }

            //新增
            QPushButton *pushButtonAdd = tabContent2->findChild<QPushButton*>("pushButtonAdd");
            if (pushButtonAdd) {

                pushButtonAdd->move(250, tabContent2->height()-200);
                pushButtonAdd->setStyleSheet("background-color: lightblue;");

                connect(pushButtonAdd, &QPushButton::clicked, [=](){

                    bool isAdd = true;
                    QVector<QStringList> vector;
                    for(int row = 0; row < tableWidgetAir->rowCount(); row++){
                        QStringList data;
                        for(int column = 0; column < tableWidgetAir->columnCount(); column++){
                            QTableWidgetItem *item = tableWidgetAir->item(row, column);
                            data.append(item->text());
                        }
                        vector.append(data);
                    }

                    QFile file(airplanePath);
                    if (!file.open(QIODevice::ReadOnly)) {
                        qDebug() << "fail to open the file";
                        return;
                    }

                    QTextStream in(&file);
                    int m = 0;
                    while (!in.atEnd()) {
                        QString line = in.readLine();
                        QStringList fields = line.split(" ", QString::SkipEmptyParts);
                        if(m >= vector.size()){
                            isAdd = false;
                            break;
                        }
                        if(vector[m] != fields){
                            isAdd = false;
                            break;
                        }
                        else{
                            m++;
                        }

                    }

                    if(isAdd){
                        int rowCount = tableWidgetAir->rowCount();
                            tableWidgetAir->insertRow(rowCount);//insertRow() 方法中的参数表示要插入的新行的索引位置

                            for (int col = 0; col < tableWidgetAir->columnCount(); ++col) {
                                QTableWidgetItem *item = new QTableWidgetItem("");

                                QFont font;
                                font.setPointSize(12);
                                item->setFont(font);
                                item->setTextAlignment(Qt::AlignCenter);

                                item->setFlags(item->flags() | Qt::ItemIsEditable); // 设置为可编辑
                                tableWidgetAir->setItem(rowCount, col, item);
                            }
                    }
                    else{
                        QMessageBox::warning(this, "新增位置不合理", "新增只能在全部航班中");
                    }
               });
        }
        //新增的确认按钮
        QPushButton *pushButtonRight1 = tabContent2->findChild<QPushButton*>("pushButtonRight1");
        if (pushButtonRight1) {

            pushButtonRight1->move(350, tabContent2->height()-200);
            pushButtonRight1->setStyleSheet("background-color: lightblue;");

            connect(pushButtonRight1, &QPushButton::clicked, [=](){

                tableWidgetAir->clearSelection();
                int rowCount = tableWidgetAir->rowCount();
                int colCount = tableWidgetAir->columnCount();
                bool rowIncomplete = false;

                // 检查最后一行是否写完整
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = tableWidgetAir->item(rowCount - 1, col);
                    if (!item || item->text().isEmpty()) {
                        rowIncomplete = true;
                        break;
                    }
                }

                if (rowIncomplete) {
                    QMessageBox::warning(this, "航班信息不完整", "添加失败");
                    for (int col = 0; col < colCount; ++col) {
                        QTableWidgetItem *item = tableWidgetAir->item(rowCount - 1, col);
                        if (item) {
                            delete item;
                        }
                    }
                    tableWidgetAir->removeRow(rowCount - 1);
                }
                else {

                    //检测航班号是否唯一
                    int c = 0;
                    for (int row = 0; row < tableWidgetAir->rowCount()-1; ++row){
                        QTableWidgetItem *item = tableWidgetAir->item(row, c);
                        for(int j = row + 1;j <= tableWidgetAir->rowCount()-1; j++){
                            QTableWidgetItem *item1 = tableWidgetAir->item(j, c);
                            if(item->text() == item1->text()){
                                QMessageBox::warning(this, "航班号唯一", "不能实现");
                                createAirWidget(tableWidgetAir);
                                return;
                            }
                        }
                    }

                  QFile file1(airplanePath);
                  //追加方式打开
                  if (!file1.open(QIODevice::Append)) {
                    // 文件打开失败，处理错误
                      qDebug() << "fail to open the file";
                      return;
                  }

                 QTextStream out(&file1);

                // 获取最后一行的数据并写入到文本文件中
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = tableWidgetAir->item(rowCount - 1, col);
                    if (item) {
                        out << item->text() << " ";
                    }
                }
                out << "\n";

                file1.close();
                // 设置最后一行为只读状态
                for (int col = 0; col < colCount; ++col) {
                    QTableWidgetItem *item = tableWidgetAir->item(rowCount - 1, col);
                    if (item) {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 设置为只读
                    }
                }
                createAirWidget(tableWidgetAir);
          }
        });
    }
        //下拉框
        QComboBox *comboBox = tabContent2->findChild<QComboBox*>("comboBox");
        if (comboBox) {
            comboBox->move(50, tabContent2->height()-150);
        }
        //文本
        QLineEdit* lineEditSeek = tabContent2->findChild<QLineEdit*>("lineEditSeek");
        if (lineEditSeek) {
            lineEditSeek->move(150, tabContent2->height()-150);
        }

        //确认
        QPushButton *pushButtonRight2 = tabContent2->findChild<QPushButton*>("pushButtonRight2");
        if (pushButtonRight2) {

            pushButtonRight2->move(250, tabContent2->height()-150);
            pushButtonRight2->setStyleSheet("background-color: lightblue;");

            connect(pushButtonRight2, &QPushButton::clicked, [=](){

                int index = comboBox->currentIndex();
                QString newData = lineEditSeek->text();
                lineEditSeek->clear();

                // 从最后一行开始逐行删除
                for (int i = tableWidgetAir->rowCount() - 1; i >= 0; --i) {
                    tableWidgetAir->removeRow(i);
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

                        if (tableWidgetAir->columnCount() < stringList.size()) {
                            tableWidgetAir->setColumnCount(stringList.size());
                        }
                        tableWidgetAir->insertRow(row);

                        for (int column = 0; column < tableWidgetAir->columnCount(); ++column) {
                            QTableWidgetItem *item = new QTableWidgetItem(stringList[column]);

                            QFont font;
                            font.setPointSize(12);
                            item->setFont(font);
                            item->setTextAlignment(Qt::AlignCenter);
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                            tableWidgetAir->setItem(row, column, item);
                        }
                        row++;
                    }
                }

                if(row == 0){
                    QMessageBox::warning(this, "无该值", "请重试");

                }
                file.close();

            });
        }
        //恢复全部
        QPushButton *pushButtonRecover = tabContent2->findChild<QPushButton*>("pushButtonRecover");
        if (pushButtonRecover) {
            pushButtonRecover->move(350, tabContent2->height()-150);
            pushButtonRecover->setStyleSheet("background-color: lightblue;");

            connect(pushButtonRecover, &QPushButton::clicked, [=](){
                  createAirWidget(tableWidgetAir);
            });
        }
      }
    }

    QWidget *tabContent1 = ui->tabWidget->widget(1); //用户管理

    if (tabContent1) {
        //背景图
        QLabel *label1 = tabContent1->findChild<QLabel*>("label1");

        if (label1) {

            label1->move(0, 0);
            label1->setFixedSize(tabContent1->width(), tabContent1->height());

            QPixmap image(":/new/image/userman.jpg");

            // 设置图片并让其适应标签大小
            label1->setPixmap(image.scaled(label1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 设置标签大小策略
            label1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            // 允许图片缩放以适应标签
            label1->setScaledContents(true);

            label1->lower();
        }
        //返回
        QPushButton *pushButtonBack1 = tabContent1->findChild<QPushButton*>("pushButtonBack1");

        if (pushButtonBack1) {
            pushButtonBack1->setFixedSize(150,80);
            pushButtonBack1->move(tabContent1->width()-200, tabContent1->height()-300);
            pushButtonBack1->setStyleSheet("background-color: lightblue;");

            connect(pushButtonBack1, &QPushButton::clicked, [=](){
                emit back();
            });
        }
        //退出
        QPushButton *pushButtonQuit1 = tabContent1->findChild<QPushButton*>("pushButtonQuit1");

        if (pushButtonQuit1) {
            pushButtonQuit1->setFixedSize(150,80);
            pushButtonQuit1->move(tabContent1->width()-200,
                             tabContent1->height()-200);
            pushButtonQuit1->setStyleSheet("background-color: lightblue;");

            connect(pushButtonQuit1, &QPushButton::clicked, [=](){
                this->close();
            });
        }
        //用户表格
        QTableWidget *tableWidget = tabContent1->findChild<QTableWidget*>("tableWidgetUser");

        if (tableWidget) {

            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);//水平表头的列宽设置为自动拉伸以填充整个表格的宽度,宽和高都会变化
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            tableWidget->setStyleSheet("QTableWidget { background-color: lightblue; }");
            tableWidget->move(this->width()/2 - tableWidget->width()/2, 20);

            createUserWidget(tableWidget);
            //编辑
            QPushButton *pushButtonEdit = tabContent1->findChild<QPushButton*>("pushButtonEdit");

            if (pushButtonEdit) {
                pushButtonEdit->setFixedSize(150,80);
                pushButtonEdit->move(tabContent1->width()-200, tabContent1->height()-500);
                pushButtonEdit->setStyleSheet("background-color: lightblue;");

                connect(pushButtonEdit, &QPushButton::clicked, [=](){
                    int col = 0;
                    for (int row = 0; row < tableWidget->rowCount(); ++row) {
                        QTableWidgetItem *item = tableWidget->item(row, col);
                        if (item) {
                            item->setFlags(item->flags() | Qt::ItemIsEditable); // 设置为可编辑
                        }
                    }
                });
            }
            //编辑的确认按钮
            QPushButton *pushButtonEdit1 = tabContent1->findChild<QPushButton*>("pushButtonEdit1");
            if (pushButtonEdit1) {
                pushButtonEdit1->setFixedSize(150,80);
                pushButtonEdit1->move(tabContent1->width()-200, tabContent1->height()-400);
                pushButtonEdit1->setStyleSheet("background-color: lightblue;");

                connect(pushButtonEdit1, &QPushButton::clicked, [=](){
                    tableWidget->clearSelection();
                    for (int row = 0; row < tableWidget->rowCount(); ++row) {
                        for (int col = 0; col < tableWidget->columnCount(); ++col) {
                            QTableWidgetItem *item = tableWidget->item(row, col);
                            if (item) {
                                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            }
                        }
                    }

                    flushUserFile(tableWidget);

                });
            }

         }
     }

    QWidget *tabContent0 = ui->tabWidget->widget(0); //票务信息

    if (tabContent0) {
        //背景图
        QLabel *label = tabContent0->findChild<QLabel*>("labelInfo");

        if (label) {

            label->move(0, tabContent0->height()-label->height());

            QPixmap image(":/new/image/seek.jpg"); // 加载图片

//            // 设置图片并让其适应标签大小
            label->setPixmap(image.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

//            // 设置标签大小策略
            label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

//            // 允许图片缩放以适应标签
            label->setScaledContents(true);

            label->lower();
        }


        //返回
        QPushButton *pushButtonBack0 = tabContent0->findChild<QPushButton*>("pushButtonBack0");

        if (pushButtonBack0) {
            pushButtonBack0->setFixedSize(150,80);
            pushButtonBack0->move(tabContent0->width()-300, tabContent0->height()-300);
            pushButtonBack0->setStyleSheet("background-color: lightblue;");

            connect(pushButtonBack0, &QPushButton::clicked, [=](){
                emit back();
            });
        }
        //退出
        QPushButton *pushButtonQuit0 = tabContent0->findChild<QPushButton*>("pushButtonQuit0");

        if (pushButtonQuit0) {
            pushButtonQuit0->setFixedSize(150,80);
            pushButtonQuit0->move(tabContent0->width()-300, tabContent0->height()-200);
            pushButtonQuit0->setStyleSheet("background-color: lightblue;");

            connect(pushButtonQuit0, &QPushButton::clicked, [=](){
                this->close();
            });
        }
        //订单详情
        QTableWidget *tableWidget = tabContent0->findChild<QTableWidget*>("tableWidgetInfo");

        if (tableWidget) {

            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            tableWidget->setStyleSheet("QTableWidget { background-color: lightblue; }");
            tableWidget->move(tabContent0->width()/2-tableWidget->width()/2, 0);

            QLineEdit *textEdit = tabContent0->findChild<QLineEdit*>("lineEditUser");

            if (textEdit) {

                textEdit->setStyleSheet("background-color: lightblue;");
                textEdit->move(tabContent0->width()/4,  tabContent0->height()-300);
            }

            QLineEdit *textEdit1 = tabContent0->findChild<QLineEdit*>("lineEditInput");

            if (textEdit1) {

                textEdit1->move(tabContent0->width()/4 + 150, tabContent0->height()-300);
            }


            QPushButton *pushButton = tabContent0->findChild<QPushButton*>("pushButtonSure");

            if (pushButton) {

                pushButton->move(tabContent0->width()/4 + 300, tabContent0->height()-300);
                pushButton->setStyleSheet("background-color: lightblue;");

                connect(pushButton, &QPushButton::clicked, [=](){
                       QString text = textEdit1->text();
                       textEdit1->clear();

                       QFile file(userPath);
                       if (!file.open(QIODevice::ReadOnly)) {
                           qDebug() << "fail to open the file";
                           return;
                       }

                       // 读取文件内容
                       QTextStream in(&file);
                       QStringList stringList;

                       bool isExist = false;
                       while (!in.atEnd()) {
                           QString line = in.readLine();
                           QStringList fields = line.split(" ", QString::SkipEmptyParts);
                           if(fields[0] == text){
                               isExist = true;
                               if(fields[3] == "否"){
                                   QMessageBox::information(this, "提示","未预订");
                                   return;
                               }
                               for(int i = 4; i < 9; i++){
                                   stringList.append(fields[i]);
                               }
                           }
                       }

                       if(!isExist){
                           QMessageBox::warning(this, "用户不存在", "请重试");
                           return;
                       }

                       file.close(); // 关闭文件

                       QFile file1(airplanePath);
                       if (!file1.open(QIODevice::ReadOnly)) {
                           qDebug() << "fail to open the file";
                           return;
                       }


                       QTextStream in1(&file1);
                       int row = 0;
                       // 逐行读取文件内容并加载到 QTableWidget 中
                       while (!in1.atEnd()) {
                           QString line = in1.readLine();
                           QStringList fields = line.split(" ", QString::SkipEmptyParts);
                           for(int i = 0; i < stringList.count(); i++){

                               if(fields[0] == stringList[i]){
                                   tableWidget->insertRow(row);

                                   for (int column = 0; column < tableWidget->columnCount(); ++column) {

                                       QTableWidgetItem *item = new QTableWidgetItem(fields[column]);

                                       QFont font;
                                       font.setPointSize(20);
                                       item->setFont(font);
                                       item->setTextAlignment(Qt::AlignCenter);
                                       item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                                       tableWidget->setItem(row, column, item);
                                   }
                                   row++;
                               }
                           }
                       }

                       file1.close();
                });
            }
            //清空
            QPushButton *pushButtonClear = tabContent0->findChild<QPushButton*>("pushButtonClear");
            if (pushButtonClear) {

                pushButtonClear->move(tabContent0->width()/4 + 450, tabContent0->height()-300);
                pushButtonClear->setStyleSheet("background-color: lightblue;");

                connect(pushButtonClear, &QPushButton::clicked, [=](){
                    int rowCount = tableWidget->rowCount();
                    // 从最后一行开始逐行删除
                    for (int i = rowCount - 1; i >= 0; --i) {
                        tableWidget->removeRow(i);
                    }
                });
            }
        }
    }
}

ManInterface::~ManInterface()
{
    delete ui;
}
