#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);

signals:
    //自定义信号
    void someSignal();

    //带参数和返回值
    int addSignal(int a,int b);
};

#endif // SENDER_H
