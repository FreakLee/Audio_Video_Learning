#include "mainwindow.h"

#include <QApplication>

#include "receiver.h"
#include "sender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Sender sender;
    Receiver receiver;

    // 连接信号与自定义槽函数
    QObject::connect(&sender, &Sender::someSignal, &receiver, &Receiver::mySlot);
    QObject::connect(&sender, &Sender::addSignal, &receiver, &Receiver::handleAddSignal);

    // 连接信号与 Lambda 表达式
    QObject::connect(&sender, &Sender::someSignal, []() {
        qDebug() << "Lambda slot called";
    });

    // 发射信号
    emit sender.someSignal();
    int result = emit sender.addSignal(4,6);
    qDebug() << "addSignal(4,6) =" << result;

    return a.exec();
}
