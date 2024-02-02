#ifndef MANINTERFACE_H
#define MANINTERFACE_H

#include <QMainWindow>
#include "airplane.h"
#include <QtAlgorithms>

namespace Ui {
class ManInterface;
}

class ManInterface : public QMainWindow
{
    Q_OBJECT

public:

    explicit ManInterface(QWidget *parent = nullptr);
    ~ManInterface();

private:
    void paintEvent(QPaintEvent *event);
    void createAirWidget(QTableWidget* tableWidget);
    void createUserWidget(QTableWidget* tableWidget);
    void flushAirFile(QVector<QStringList> vector);
    void flushUserFile(QTableWidget *tableWidget);
    void sort(QVector<QStringList>& vectorAll, QVector<QStringList> vector);

    Ui::ManInterface *ui;

signals:
    void back();
};

#endif // MANINTERFACE_H
