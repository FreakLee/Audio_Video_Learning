#include "receiver.h"
#include <QDebug>

Receiver::Receiver(QObject *parent)
    : QObject{parent}
{

}

void Receiver:: mySlot ()
{
    qDebug() << "Custom slot called!";
}

int Receiver::handleAddSignal(int a, int b)
{
    qDebug() << "Receiver::handleAddSignal";

    return a + b;
}
