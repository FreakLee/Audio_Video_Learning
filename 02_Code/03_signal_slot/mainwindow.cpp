#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *btn = new QPushButton;
    btn->setText("关闭");
    btn->setFixedSize(100, 40);
    btn->move(100, 100);
    btn->setParent(this);

    //连接
    connect(btn, &QPushButton::clicked,this, &MainWindow::close);

    //断开连接
    //disconnect(btn, &QPushButton::clicked,this, &MainWindow::close);

    //可以通过ui->变量名访问
    ui->loginButton->setFixedHeight(44);

    ui->passwordEdit->setPlaceholderText("请输入密码");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::on_loginButton_clicked()
{
    qDebug() << "on_loginButton_clicked";
}


void MainWindow::on_passwordEdit_textChanged()
{
    // 获取文本内容
    QString text = ui->passwordEdit->toPlainText();
    qDebug() << "Text content:" << text;
}

