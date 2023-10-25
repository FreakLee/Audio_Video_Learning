#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //槽函数声明
    void on_pushButton_clicked();

    //手动添加槽函数声明
    void on_loginButton_clicked();

    void on_passwordEdit_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
