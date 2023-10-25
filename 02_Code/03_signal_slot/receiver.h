#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);

public slots:
    //自定义槽函数
    void mySlot();

    int handleAddSignal(int a,int b);
};

#endif // RECEIVER_H
