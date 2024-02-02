#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QDir>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTabBar>
#include <QHeaderView>
#include <QTextBlock>

//关于检索我用在了航班界面，做的用户界面较粗糙（没设key,但认定用户名是key）
// 有想法：将文件读到vector中，vector每个元素加上索引（文件中的一行一行），排成有序，用折半查找，找到并修改，直接用文件指针
// 指向代更改的位置修改即可

//用的绝对路径，至于相对路径或将txt文件放入resource文件中都不行，resource通常存放像图片的二进制，不能直接写；
//执行该程序linux的工作目录该项目的文件夹
//#define airplanePath "/root/system/airplaneFile.txt"
//#define userPath "/root/system/user.txt"
//#define announcePath "/root/system/announcement.txt"

//#define airplanePath "/root/build-system-Desktop_Qt_5_12_12_GCC_64bit-Debug/airplaneFile.txt"
//#define userPath "/root/build-system-Desktop_Qt_5_12_12_GCC_64bit-Debug/user.txt"
//#define announcePath "/root/build-system-Desktop_Qt_5_12_12_GCC_64bit-Debug/announcement.txt"


//打包项目时用的路径（一般打包就是build-system-Desktop_Qt_5_12_12_GCC_64bit-Realse文件夹）
//工作目录是指当前目录，运行目录是指exe所在路径
//QCoreApplication::applicationDirPath() 返回当前应用程序的可执行文件所在的目录路径
//QDir::separator() 是一个用于获取操作系统路径分隔符的函数，它返回适合当前操作系统的分隔符（在Windows上是 \，在Unix和类Unix系统上是 /）
//QDir::cleanPath() 是 Qt 中 QDir 类的一个静态方法，用于规范化和清理给定的文件路径。它会处理路径中的斜杠、点和其他字符，确保路径格式是标准的、规范化的，并且在不同操作系统下都能正确识别和使用。

//重复的斜杠：多个连续的斜杠会被压缩为一个斜杠。
//点号：. 表示当前目录，.. 表示父目录。它会根据路径中的点号来处理路径的转换。
//路径分隔符：它会使用适当的路径分隔符，比如在 Windows 下是反斜杠 \，在 Unix/Linux 下是正斜杠 /
//Windows 系统上会将所有斜杠转换为反斜杠 \，而在 Unix/Linux 系统上则会将所有斜杠转换为正斜杠 /
#define airplanePath QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("airplaneFile.txt"))
#define userPath QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("user.txt"))
#define announcePath QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("announcement.txt"))
#define managerPath QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("manager.txt"))


//对于interface中的tabWidget没有隐藏表头，userinterface中的tabWidget隐藏表头并使用pushButton来进入某一选项卡,一般实现都是第二种方式
//对于样式表在ui界面设置即可，这次都用的代码设置的
#endif // AIRPLANE_H
