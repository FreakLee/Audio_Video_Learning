## FFmpeg

[FFmpeg](https://zh.wikipedia.org/wiki/FFmpeg) 是一个免费、开源且跨平台的音视频处理工具套件，它提供了丰富的功能和命令行接口，用于在音视频领域进行编解码、转码、剪辑、过滤等操作。它由Fabrice Bellard创建，并于2000年首次发布，是一个功能强大且广泛应用的音视频处理工具，适用于各种音视频处理需求和应用场景。无论是简单的格式转换还是复杂的流处理，FFmpeg都提供了丰富的功能和工具，是音视频开发和处理的重要工具之一。

### 功能与特点

FFmpeg提供了强大而灵活的命令行接口，用户可以使用命令行参数来指定输入文件、输出文件、编解码器、滤镜和其他参数。同时，FFmpeg也提供了一些编程接口，如libavcodec、libavformat等，使得开发人员可以通过编程方式使用FFmpeg的功能。

* 支持广泛的音视频格式：FFmpeg支持几乎所有常见的音视频格式，包括但不限于MP4、AVI、MKV、FLV、MP3、AAC等。它可以进行格式之间的转换，使得用户可以轻松地处理和转码不同格式的音视频文件。

* 强大的编解码能力：FFmpeg支持多种音视频编解码器，包括H.264、H.265、MPEG-4、VP9、AAC、MP3等。这使得用户可以对音视频文件进行解码、编码和重新编码，以满足不同的需求和要求。

* 实时流处理和转码：FFmpeg可以处理实时音视频流，包括网络流、摄像头捕获、屏幕录制等。它能够对这些流进行编码、解码、转码和传输，适用于实时流媒体、视频会议等应用场景。

* 视频剪辑和处理：FFmpeg提供了丰富的视频处理功能，可以进行剪辑、裁剪、旋转、调整大小、添加水印、调整亮度对比度等操作。这使得用户可以对视频进行各种编辑和处理，满足不同的需求和创意。

* 音频处理和混音：FFmpeg可以进行音频的提取、转码、混音、音量调整等操作。用户可以使用FFmpeg处理音频文件，如剪辑音频片段、转换音频格式、调整音频质量等。

* 视频滤镜和特效：FFmpeg提供了丰富的视频滤镜和特效，用于改变视频的外观和效果。用户可以应用滤镜、添加文字、模糊、锐化、颜色调整等，以实现各种视觉效果。

* 跨平台支持：FFmpeg可在多个操作系统平台上运行，包括Windows、macOS、Linux等。这使得开发人员和用户可以在不同的环境中使用和集成FFmpeg。

### 安装

可以通过[官网下载页面](https://ffmpeg.org/download.html)下载对应的安装包安装，也可以利用 Homebrew工具通过终端安装：

```
brew install ffmpeg
```

安装完毕后，可以查看版本信息检查是否安装成功：

```
ffmpeg -version
```

若安装成功会得到如下类似信息：

```
ffmpeg version 6.0 Copyright (c) 2000-2023 the FFmpeg developers
built with Apple clang version 14.0.0 (clang-1400.0.29.202)
```

### 目录结构

可以通过电脑 Finder->Go->Go to Folder输入目录：/usr/local/Cellar/ffmpeg，进入目录中。![结构如下](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.1.png)


## Qt

[Qt](https://zh.wikipedia.org/wiki/Qt) （/ˈkjuːt/，发音同“cute”）是一个跨平台的C++应用程序开发框架，广泛用于开发图形界面应用程序、嵌入式系统和移动应用等。它由Qt公司（前身为Nokia）开发并维护，具有丰富的功能和工具，被广泛应用于多个行业和领域。

### 功能与特点

下面是 Qt 框架的一些主要特点和功能：

* 跨平台支持：Qt提供了很好的跨平台支持，可以在多个操作系统上运行，包括Windows、macOS、Linux、Android和iOS等。开发者可以使用同一套代码在不同平台上构建应用程序，减少了开发和维护的工作量。

* 组件库和界面设计：Qt提供了丰富的组件库和工具，可以轻松创建现代化和吸引人的图形界面。它包括各种预定义的控件（如按钮、文本框、表格等），以及支持主题和样式定制的机制，使得开发者可以根据需求定制应用程序的外观和交互方式。

* 信号与槽机制：Qt引入了信号与槽机制，通过信号和槽的连接，实现了组件之间的事件通信和交互。这种机制使得开发者可以轻松地实现模块化和松耦合的设计，提高了代码的可读性和可维护性。

* 数据库支持：Qt提供了数据库访问模块，支持多种数据库系统，如MySQL、SQLite、PostgreSQL等。开发者可以使用这些模块进行数据库连接、查询和操作，方便地处理应用程序的数据存储和管理。

* 多媒体和图形处理：Qt提供了多媒体模块，包括对音频、视频和图像的处理和播放功能。开发者可以使用这些模块实现音视频播放、图像处理、图形绘制等功能，为应用程序增加丰富的多媒体体验。

* 网络和通信：Qt提供了网络模块，支持TCP/IP和UDP等网络通信协议。开发者可以使用这些模块进行网络编程，实现网络通信、数据传输和远程访问等功能。

* 多线程支持：Qt提供了多线程编程的支持，包括线程管理、线程同步和并发编程等功能。开发者可以使用这些功能来实现并发处理、任务分配和资源管理，提高应用程序的性能和响应能力。

除了上述功能外，Qt还提供了许多其他模块和工具，如XML处理、国际化和本地化支持、OpenGL集成、Web引擎等，以满足不同应用场景的需求。

### 安装

同样的，可以直接去[官网](https://www.qt.io/download)下载对应平台的安装包进行安装，也可以通过brew工具安装：

```
brew install qt
```

安装完毕后，会存于：/usr/local/Cellar/qt目录下，有类似如下信息：

```
You can add Homebrew's Qt to QtCreator's "Qt Versions" in:
  Preferences > Qt Versions > Link with Qt...
pressing "Choose..." and selecting as the Qt installation path:
  /usr/local
```

安装 Qt Creator（IDE）

```
brew install --cask qt-creator
```

安装成功，存放于：/usr/local/Caskroom/qt-creator

```
==> Installing Cask qt-creator
==> Moving App 'Qt Creator.app' to '/Applications/Qt Creator.app'
🍺  qt-creator was successfully installed!
```

### 配置

打开 Qt Creator应用程序，在其偏好设置里配置 Qt 路径![偏好设置](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.3.png)

根据前文可知，Qt的路径在/usr/local/Cellar/qt，使用快捷键Command + Shift + G手动输入这个文件夹，然后选择 qt/6.5.2/bin/qmake，点击open![qmake](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.4.png)

点击 OK![确认](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.5.png)

### 设置默认kits

依旧选择Qt 应用程序的偏好设置，选中kits，选择对应机器的kit（终端输入如下命令可以知晓自己电脑多少位：uname -a）![kits](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.6.png)

滑动到最底部，选择 Qt 版本，然后点击 OK![Qt Version](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.7.png)

## 第一 Qt 程序

### 创建项目

打开 Qt，File->New Project，或者快捷键：shift+command+N。选择 Qt Widgets Application![选模板](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.8.png)

输入完项目名字，选择存放代码的目录![项目名字](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.9.png)

选 Build System![Build System](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.10.png)

输入详细信息![Details](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.11.png)

勾选上 Generate form 的话会创建一个默认的 mainwindow.ui 文件。有点类似iOS开发中的xib，可以直接拖放 UI 控件。

选 kits![Kit Selection](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.12.png)

项目创建完成![Done](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.13.png)

项目结构如下![项目结构](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.16.png)

* .pro文件，项目配置文件
* Headers文件夹，存放头文件
* Source文件夹，存放代码之类的，如.cpp文件
* Formse文件夹，存放UI文件

``` cpp
//main.cpp
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
```

运行项目![运行效果](https://github.com/FreakLee/Audio_Video_Learning/blob/main/03_Resource/Image/01.14.png)

### 集成FFmpeg

修改.pro文件，在文件中添加如下配置信息

```
# 设置头文件路径
INCLUDEPATH += /usr/local/Cellar/ffmpeg/6.0_1/include

# 设置库文件路径
LIBS += -L/usr/local/Cellar/ffmpeg/6.0_1/lib \
        -lavcodec \
        -lavdevice \
        -lavfilter \
        -lavformat \
        -lavutil \
        -lpostproc \
        -lswscale \
        -lswresample
```

测试是否集成成功，在main.cpp添加几行代码，尝试打印 libavcodec.a库文件的版本信息

``` cpp
#include "mainwindow.h"

#include <QApplication>

#include <QDebug>

extern "C" {
#include <libavcodec/avcodec.h>
}

int main(int argc, char *argv[])
{
    qDebug() << av_version_info();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
```

