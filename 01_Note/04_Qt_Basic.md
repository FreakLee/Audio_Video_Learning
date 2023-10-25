Qt基于C++编程语言，利用了面向对象编程的概念和技术。它使用了所谓的"信号和槽"机制来处理事件和通信，这是Qt的核心特性之一。Qt还提供了丰富的类库，涵盖了从基本的数据结构到高级功能的各个方面，使开发者能够快速构建复杂的应用程序。


Qt的语法与标准的C++语法非常相似，同时也引入了一些新的[概念](https://doc.qt.io/qt-6/qtcore-index.html)和关键字。以下是一些常用的语法元素和概念：

* QObject和QWidget：QObject是Qt中所有类的基类，提供了信号和槽机制以及对象间的通信功能。QWidget是可视化界面的基类，用于创建窗口和其他可视化组件。
* 信号和槽：信号是一种特殊的函数，用于通知事件的发生。槽是响应信号的函数。可以使用connect()函数将信号与槽连接起来，实现事件的处理和通信。
* 可查询和可设计的对象属性
* 分层和可查询的对象树，使用受保护的指针以自然的方式组织对象所有权
* 布局管理器：Qt提供了多种布局管理器，用于自动排列和调整窗口和组件的大小。常用的布局管理器包括 QVBoxLayout、QHBoxLayout和QGridLayout。
* 事件处理：Qt使用事件机制来处理用户输入和其他系统事件。可以通过重写事件处理函数来捕获和处理不同类型的事件。
* Qt类库：Qt提供了丰富的类库，包括用于处理字符串、文件、网络、数据库、图形和多媒体等功能的模块。

## Qt控制台应用程序

Qt也支持控制台程序。进入项目编写一个简单的HelloWorld程序。

``` sh
cd /your_project_path/Code/02_QtConsoleApp
touch touch qt_console_app.cpp
vim qt_console_app.cpp
```

然后输入以下代码：

```cpp
#include <QTextStream>

int main() {
 QTextStream(stdout) << "Hello, world!" << Qt::endl;
 return 0;
}
```

接着在终端输入以下命令（确保仍在项目所在目录）：

``` sh
qmake -project
```
执行完这条命令后会生成跟目录同名的.pro文件，用于描述项目。我这里是：02_QtConsoleApp.pro。

继续输入命令qmake 命令生成 Makefile：

``` sh
qmake
```
此时会生成一个Makefile文件，然后输入make命令进行编译：
``` sh
make
```

此时编译成功本应该生成一个qt_console_app的可执行文件。结果生成了与.cpp同名的.o文件，即：qt_console_app.o，还生成了目录同名的02_QtConsoleApp.app应用程序。
![2.1](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/02.01.jpg)

尝试去执行这个.o文件会报错，格式错误：
``` sh
./qt_console_app.o
zsh: exec format error: ./qt_console_app.o
```
如果权限不够，先更改权限：
``` sh
chmod +x qt_console_app.o
```
用file查看其信息：
```
file  qt_console_app.o
```
发现其只是目标文件：
``` sh
qt_console_app.o: Mach-O 64-bit object x86_64
```
这时候需要通过gcc链接Qt动态库（Qt安装路径中lib下的QtCore.framework），生成可执行文件：
``` sh
g++ -o qt_console_app qt_console_app.o -F /usr/local/Cellar/qt/6.5.2/lib -framework QtCore
```
此时生成了qt_console_app可执行文件
![2.2](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/02.02.jpg)

运行可执行文件：
``` sh
./qt_console_app
```
控制台成功打印：Hello, world!

查看文件信息，显然跟上面的qt_console_app.o不一样：
``` sh
qt_console_app: Mach-O 64-bit executable x86_64
```
事实上，上面make命令生成的02_QtConsoleApp.app，显示包内容，然后可以找到可执行文件。
![2.3](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/02.03.jpg)
通过这个简单的Qt控制台程序，很容易联想到以前在终端编译、链接、执行C程序的过程。

## 元对象系统（meta-object system）

[Qt的元对象系统](https://doc.qt.io/qt-6/metaobjects.html)为对象间通信、运行时类型信息和动态属性系统提供了信号和槽机制。

在Qt中，每个继承自QObject的类都有一个与之对应的元对象（Meta Object）。元对象存储了关于类的结构和特性的信息，包括类名、父类名、信号、槽函数、属性等。元对象通过元对象编译器（MOC，Meta-Object Compiler）在编译时生成，并作为每个QObject派生类的静态成员。

元对象系统的一些核心概念和用法包括：

* **元属性（Meta Property）**：元属性描述了QObject派生类中的属性。每个属性都有名称、类型、读写权限等信息。元属性可以通过元对象系统进行查询、读取和修改。可以使用QMetaObject类的方法，如propertyCount()、property()、read()、write()等来操作元属性。

* **元方法（Meta Method）**：元方法描述了QObject派生类中的成员函数。每个方法都有名称、参数列表、返回类型等信息。通过元对象系统，可以在运行时调用对象的成员函数。可以使用QMetaObject类的方法，如methodCount()、method()、invokeMethod()等来操作元方法。

* **信号与槽（Signals and Slots）**：元对象系统是信号与槽机制的基础。通过元对象系统，可以在运行时连接信号和槽，并在信号发射时自动调用槽函数。信号与槽机制使用了元对象系统提供的元方法信息来实现类型安全的对象间通信。

* **运行时类型识别（Run-time Type Identification，RTTI）**：元对象系统提供了RTTI的功能，使得在运行时可以判断一个QObject对象的实际类型。可以使用QMetaObject类的方法，如className()、inherits()等来获取和比较对象的类型信息。

除了上述核心概念，Qt还提供了一些额外的工具和类来操作元对象系统，例如：

* QMetaObject类：表示元对象的类，提供了访问元属性、元方法、信号、槽等的方法。
* QMetaProperty类：表示元属性的类，提供了访问属性名称、类型、读写权限等的方法。
* QMetaMethod类：表示元方法的类，提供了访问方法名称、参数列表、返回类型等的方法。
* QMetaEnum类：表示枚举类型的类，提供了访问枚举名称和值的方法。
* QMetaType类：提供了在元对象系统中注册和操作用户自定义类型的方法。
* QMetaCallEvent类：表示调用元方法的事件，用于在事件循环中传递元方法调用。

C++ moc 本质上为我们提供了Objective-C或Java运行时环境的灵活性，同时保持了C++独特的性能和可扩展性优势。

使用元对象系统，可以在运行时动态地获取和操作类的成员、属性和函数，而无需事先知道其具体类型。这为Qt提供了很多强大的功能，例如动态创建对象、动态调用函数、动态绑定信号与槽等。

## 信号与槽

在Qt中，信号与槽是一种用于实现对象间通信的机制，是一种回调技术的替代方案。它是Qt框架中的核心特性之一，用于处理事件和消息的传递。信号用于发出事件或状态的通知，而槽用于接收并响应这些通知。

![Signals & Slots](https://doc.qt.io/qt-6/images/abstract-connections.png)

概念：

* 信号（Signal）：信号是一种特殊的成员函数，它可以由对象发出，用于通知其他对象发生了某个事件或状态的变化。信号可以在任何时刻被发射。
* 槽（Slot）：槽是普通的成员函数，用于接收信号，并对信号做出响应。槽函数可以执行任何逻辑操作，如修改对象的状态、执行计算等。
* 连接（Connection）：连接是将信号与槽函数关联起来的过程。当信号被发射时，与之连接的槽函数将被自动调用。
* 信号与槽的关联是通过Qt的元对象系统来实现的，它在运行时动态地建立和管理信号与槽之间的连接关系。

特点：

* 每个 QObject 类都可以有任意数量的信号和插槽
* 只能从该类（信号所在的位置）发出信号
* 可以将信号与另一个信号连接（制作信号链）
* 信号的发送方跟接收方可以来自同一个类
* 每个信号和槽都可以与其他信号和槽有无限数量的连接
* 所有包含信号或槽的类都必须直接或者间接继承 QObject 类
* 不能在插槽属性中设置默认值，比如：void mySlot(int i = 0)
* 信号由 moc（Meta-Object-Compiler）自动生成，不得在 .cpp 文件中实现

语法：

* 定义信号：在类的声明中使用 signals 关键字定义信号，通常放在 signals 访问修饰符下。
* 定义槽：在类的声明中定义普通成员函数作为槽，可以放在 public、protected 或 private 访问修饰符下。
* 连接信号与槽：使用 QObject::connect() 函数来建立信号与槽的连接。连接时需要指定发送信号的对象、发射的信号、接收信号的对象以及处理信号的槽函数。

连接信号：
``` cpp
QObject::connect (
  const QObject * sender,
  const char * signal,
  const QObject * receiver,
  const char * method
);
``` 

断开信号：
``` cpp
QObject::disconnect (
  const QObject * sender,
  const char * signal,
  const QObject * receiver,
  const char * method
);
```

### 代码示例

在mainwindow.cpp中创建一个QPushButton，添加到mainwindow上面，然后发送按钮的点击信号，接收者为mainwindow，触发window的close方法。

``` cpp
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
}
```

### ui示例

在ui中建立信号与槽的连接更加简单。这种方式跟iOS开发中的xib非常类似。点击mainwindow.ui，然后随便拖一个Push Button，右击选择“Go to slot”。

![2.4](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/02.04.jpg)

选择第一个，点击OK。

![2.5](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/02.05.jpg)

接着自动生成了槽函数的声明和实现。在实现函数里随意加点代码。

``` cpp
void MainWindow::on_pushButton_clicked()
{
    close();
}
```

根据生成的槽函数与Button名字的之间的特点，可以猜想它们之间可能有某种联系。带着这个猜想再拖一个Button，命名为：loginButton。

![2.6](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/02.06.jpg)

不在.ui文件中进行信号与槽的连接，而是仿照上面的方式分别在mainwindow.h添加槽函数声明：
``` cpp
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

private:
    Ui::MainWindow *ui;
};

```

在mainwindow.cpp添加槽函数实现：
``` cpp
void MainWindow::on_loginButton_clicked()
{
    qDebug() << "on_loginButton_clicked";
}
```
运行程序，点击loginButton，有打印：on_loginButton_clicked。因此，我们可以得出一个结论，此类槽函数的命名规则：*on*\_**控件的变量名**\_**事件名**。ui文件中的控件会根据符合命名规则的槽函数自动建立连接。

### 自定义信号与槽

分别创建一个发送方的类Sender和接收方的类Receiver。

1、SENDER_H
``` cpp
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
```
信号不需要手动实现，所以sender.cpp啥都不需要写。

2、RECEIVER_H
``` cpp
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

```
3、receiver.cpp
``` cpp
void Receiver:: mySlot ()
{
    qDebug() << "Custom slot called!";
}

int Receiver::handleAddSignal(int a, int b)
{
    qDebug() << "Receiver::handleAddSignal";

    return a + b;
}
```
4、在main.cpp测试一下
``` cpp
    Sender sender;
    Receiver receiver;

    // 连接信号与自定义槽函数
    QObject::connect(&sender, &Sender::someSignal, &receiver, &Receiver::mySlot);
    QObject::connect(&sender, &Sender::addSignal, &receiver, &Receiver::handleAddSignal);

    // 发射信号
    emit sender.someSignal();
    int result = emit sender.addSignal(4,6);
    qDebug() << "addSignal(4,6) =" << result;
```

### 使用 Lambda 表达式作为槽函数

当处理信号时，可以使用 Lambda 表达式作为槽函数，而不必显式定义一个成员函数。Lambda 表达式可以在信号发射时执行特定的代码逻辑。

Lambda 表达式的语法为 \[捕获列表](参数列表) { 函数体 }。

在上述示例中发射信号前插入如下代码：

``` cpp
    // 连接信号与 Lambda 表达式
    QObject::connect(&sender, &Sender::someSignal, []() {
        qDebug() << "Lambda slot called";
    });
```

## 参考

[1、Signals & Slots](https://doc.qt.io/qt-6/signalsandslots.html)<br>

[2、How to Use Signals and Slots](https://wiki.qt.io/How_to_Use_Signals_and_Slots)<br>

[3、Why Does Qt Use Moc for Signals and Slots?](https://doc.qt.io/qt-5/why-moc.html)



