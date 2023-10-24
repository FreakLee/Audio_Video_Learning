Qt基于C++编程语言，利用了面向对象编程的概念和技术。它使用了所谓的"信号和槽"机制来处理事件和通信，这是Qt的核心特性之一。Qt还提供了丰富的类库，涵盖了从基本的数据结构到高级功能的各个方面，使开发者能够快速构建复杂的应用程序。


Qt的语法与标准的C++语法非常相似，同时也引入了一些新的[概念](https://doc.qt.io/qt-6/qtcore-index.html)和关键字。以下是一些常用的语法元素和概念：

* QObject和QWidget： QObject是Qt中所有类的基类，提供了信号和槽机制以及对象间的通信功能。QWidget是可视化界面的基类，用于创建窗口和其他可视化组件。
* 信号和槽： 信号是一种特殊的函数，用于通知事件的发生。槽是响应信号的函数。可以使用connect()函数将信号与槽连接起来，实现事件的处理和通信。
* 可查询和可设计的对象属性
* 分层和可查询的对象树，使用受保护的指针以自然的方式组织对象所有权
* 布局管理器： Qt提供了多种布局管理器，用于自动排列和调整窗口和组件的大小。常用的布局管理器包括 QVBoxLayout、QHBoxLayout和QGridLayout。
* 事件处理： Qt使用事件机制来处理用户输入和其他系统事件。可以通过重写事件处理函数来捕获和处理不同类型的事件。
* Qt类库： Qt提供了丰富的类库，包括用于处理字符串、文件、网络、数据库、图形和多媒体等功能的模块。

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
此时生成了qt_console_app可执行文件，运行可执行文件：
``` sh
./qt_console_app
```
成功打印：Hello, world!

查看文件信息，显然跟上面的qt_console_app.o不一样：
``` sh
qt_console_app: Mach-O 64-bit executable x86_64
```

事实上，上面make命令生成的02_QtConsoleApp.app，显示包内容，然后可以找到可执行文件。通过这个简单的Qt控制台程序，很容易联想到以前在终端编译、链接、执行C程序的过程。





