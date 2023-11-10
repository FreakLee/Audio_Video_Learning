#include "mainwindow.h"

#include <QApplication>

extern "C" {
#include <libavdevice/avdevice.h>
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // 注册所有可用的设备
    avdevice_register_all();
    avformat_network_init();

    return a.exec();
}
