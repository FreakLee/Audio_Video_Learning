之前我们使用FFmpeg命令行工具进行了简单的音视频操作，这次在Mac OS环境下编写代码实现简单的音频录制功能。

## FFmpeg命令行音频录制
首先回顾一下Mac OS环境下简单的音频录制命令行实现：

``` sh
ffmpeg -f avfoundation -i ":0" -t 20 -acodec pcm_s16le -ar 44100 -ac 2 ~/Desktop/output.wav
```

参数说明：
* -f avfoundation：指定输入设备为 avfoundation，用于音频录制。
* -i ":0"：指定录制的音频输入源。
* -t 20：指定录制的时长，单位为秒。
* -acodec pcm_s16le：指定音频编码器为 pcm_s16le，即无压缩的 PCM 格式。
* -ar 44100：指定音频采样率为 44100 Hz，即每秒采样 44100 次。
* -ac 2：指定音频通道数为 2，即立体声。
* ~/Desktop/output.wav：指定输出文件路径和文件名。可以根据需要修改输出文件的格式和路径。

当然部分参数可以省略：

``` sh
ffmpeg -f avfoundation -i ":0" -t 20  ~/Desktop/output.wav
```
下面我们将编程实现简化后的音频录制功能，即录制一段20秒的音频保存在指定位置。

## 编程实现音频录制功能

利用FFmpeg的api进行音频录制操作，先了解一下其中一些常用api

### 相关API

* AVInputFormat

AVInputFormat 是 FFmpeg 中表示输入媒体格式的结构体。每个输入媒体格式（例如：MP4、AVI、FLV 等）都对应一个 AVInputFormat 结构体。它包含了该格式的名称、扩展名、支持的输入编解码器等信息。

使用 AVInputFormat 结构体，你可以根据输入文件的格式选择合适的输入格式，或者根据需要注册自定义的输入格式。

* AVOutputFormat

AVOutputFormat 是 FFmpeg 中表示输出媒体格式的结构体。每个输出媒体格式（例如：MP4、AVI、FLV 等）都对应一个 AVOutputFormat 结构体。它包含了该格式的名称、扩展名、支持的输出编解码器等信息。

使用 AVOutputFormat 结构体，你可以根据输出文件的格式选择合适的输出格式，或者根据需要注册自定义的输出格式。

* AVFrame

AVFrame 是 FFmpeg 中表示音视频帧的结构体。它包含了音视频帧的原始数据和相关的信息，如时间戳、宽度、高度等。每个 AVFrame 对应一个音频或视频帧。

AVFrame 可以用于存储解码后的音视频帧数据，以及进行音视频处理、转码等操作。它提供了用于访问和操作音视频数据的函数和成员变量，如 data、linesize、pts 等。

* AVFormatContext

AVFormatContext 是 FFmpeg 中表示音视频容器格式的上下文结构体。它包含了音视频文件的整体信息，如文件名、格式、时长、流信息等。AVFormatContext 是操作输入或输出文件的主要数据结构之一。

在音频录制或音视频处理中，你可以通过打开输入文件获得一个 AVFormatContext 结构体，用于读取输入文件的相关信息和数据流。

* AVStream

AVStream 是 AVFormatContext 中表示音视频数据流的结构体。一个 AVFormatContext 可能包含多个 AVStream，每个 AVStream 对应一个音频或视频流。

AVStream 包含了音视频流的详细信息，如编解码器、时长、帧率、采样率等。通过 AVStream，你可以获取有关音视频流的各种属性和参数。

* AVPacket

AVPacket 是 FFmpeg 中表示音视频数据包的结构体。它包含了音视频数据的压缩数据和相关的信息，如时间戳、时长等。每个 AVPacket 对应一个音频或视频帧。

在音频录制或音视频处理中，你可以使用 AVPacket 结构体来读取和写入音视频数据。当从输入文件中读取音视频帧时，它们被封装为 AVPacket 结构体；当将音视频帧写入输出文件时，也需要将它们封装为 AVPacket 结构体。

### 代码实现

一般来说，编程实现音频录制功能需要进行以下一些步骤：

* 注册设备等相关初始化操作
* 获取输入格式对象
* 打开设备
* 采集数据并写入输出文件
* 释放资源

1、创建一个Qt程序：04_record_audio

在 Mac OS上，应用程序要访问音视频设备需要添加个Info.plist。（这点对于iOS开发者来说很熟悉）。用Xcode或者其它文本编辑器创建个Info.plist文件，并写入如下类似内容并保存到项目根目录或者及其子目录。

``` xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
        <key>NSMicrophoneUsageDescription</key>
        <string>使用麦克风进行音频录制</string>
</dict>
</plist>
```

2、配置.pro文件（Info.plist文件在项目子目录mac里）

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


#设置Info.plist文件
    QMAKE_INFO_PLIST = mac/Info.plist
```

3、注册设备

``` cpp
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
```

4、打开mainwindow.ui，随意拖个按钮，然后连接槽函数

``` cpp
void MainWindow::on_audioButton_clicked()
{
    //进行音频录制操作

}
```

5、编码实现

``` cpp
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <thread>

//输入格式
#define INPUT_FMT "avfoundation"
//设备名字
#define DEVICE_NAME ":0"
//输出文件名字
#define OUTPUT_FILE_NAME "/Users/你的电脑用户名/Desktop/output.wav"

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/time.h>
}


void MainWindow::on_audioButton_clicked()
{
    ui->audioButton->setEnabled(false);

    qDebug() << "MainWindow::on_audioButton_clicked";

    // 输出文件名
    QString outputFileName = OUTPUT_FILE_NAME;//QCoreApplication::applicationDirPath() + "/output.wav";

    // 获取格式输入对象
    const AVInputFormat *inputFormat = av_find_input_format("avfoundation");

    // 输入上下文
    AVFormatContext *formatContext = nullptr;

    // 打开设备
    int result = avformat_open_input(&formatContext, DEVICE_NAME, inputFormat, nullptr);
    if (result < 0) {
        qDebug() << "设备打开失败" << av_err2str(result);
            return ;
    }

    // 文件输出上下文
    AVFormatContext *outputFormatContext = nullptr;

    // 创建输出格式上下文
    avformat_alloc_output_context2(&outputFormatContext, nullptr, nullptr, outputFileName.toUtf8().constData());
    if (!outputFormatContext) {
        qDebug() << "无法创建输出格式上下文";
        avformat_close_input(&formatContext);
        return ;
    }

    // 添加音频流
    AVStream *audioStream = avformat_new_stream(outputFormatContext, nullptr);
    if (!audioStream) {
        qDebug() << "无法创建音频流";
        avformat_close_input(&formatContext);
        avformat_free_context(outputFormatContext);
        return ;
    }

    // 复制输入设备的音频参数到输出流
    avcodec_parameters_copy(audioStream->codecpar, formatContext->streams[0]->codecpar);

    // 打开输出文件
    if (avio_open(&outputFormatContext->pb, outputFileName.toUtf8().constData(), AVIO_FLAG_WRITE) < 0) {
        qDebug() << "无法打开输出文件";
        avformat_close_input(&formatContext);
        avformat_free_context(outputFormatContext);
        return ;
    }

    // 设置录制时长为20秒
    int64_t duration = 20 * AV_TIME_BASE;  

    // 录制开始时间
    int64_t startTime = av_gettime();

    // 写入文件头
    int ret = avformat_write_header(outputFormatContext, nullptr);
    if (ret < 0) {
        qDebug() << "写入文件头失败";
        return;
    }

    // 数据包
    AVPacket *packet = av_packet_alloc();

    // 读取音频数据并写入文件，直到达到指定的录制时长或文件末尾
    while (true) {
        int readResult = av_read_frame(formatContext, packet);
        if (readResult < 0) {
            if (readResult == AVERROR_EOF) {
                // 已达到文件末尾
                break;
            } else if (readResult == AVERROR(EAGAIN)) {
                // 资源暂时不可用，等待一段时间后再次尝试
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            } else {
                // 非预期的错误发生
                qDebug() << "读取音频数据时发生错误：" << av_err2str(readResult);
                    break;
            }
        }

        if (packet->stream_index == 0) { // 只处理音频流
            av_write_frame(outputFormatContext, packet);
        }
        av_packet_unref(packet);

        // 检查录制时长是否已达到指定的时长
        int64_t currentTime = av_gettime();
        if (currentTime - startTime >= duration) {
            break;
        }
    }

    // 写入文件尾
    av_write_trailer(outputFormatContext);

    // 关闭文件
    avformat_close_input(&formatContext);
    avformat_free_context(outputFormatContext);

    qDebug() << "录制完成：" << outputFileName;

    ui->audioButton->setEnabled(true);
}

```

6、查看并播放音频

终端进入输出文件所在目录，输入：ffmpeg -i output.wav
```
Input #0, wav, from 'output.wav':
  Metadata:
    encoder         : Lavf60.3.100
  Duration: 00:00:19.99, bitrate: 2822 kb/s
  Stream #0:0: Audio: pcm_f32le ([3][0][0][0] / 0x0003), 44100 Hz, stereo, flt, 2822 kb/s
```
可以看到音频信息，时长19.99秒，跟预期几乎无差别。再输入播放命令，可正常播放，简单的音频录制功能初步实现：ffplay -i output.wav。当然也可直接点击音频文件进行播放。

### 小插曲

Mac OS环境要利用FFmpeg来编码实现音频录制功能，其实也可以写个最简单的C++程序来实现（其实是多此一举😄）

``` cpp
#include <iostream>
#include <cstdlib>

int main() {
    std::string command = "ffmpeg -f avfoundation -i \":0\" -t 20 output.wav";
    
    std::cout << "Recording audio..." << std::endl;
    
    int status = std::system(command.c_str());
    
    if (status == 0) {
        std::cout << "Audio recording completed." << std::endl;
    } else {
        std::cout << "Audio recording failed." << std::endl;
    }
    
    return 0;
}
```

然后终端进入到该程序目录，使用Clang编译器进行编译：

``` sh
clang++ -o audio_recording record_audio.cpp
```

生成一个名为 `audio_recording` 的可执行文件，运行可执行文件：

``` sh
./audio_recording
```
很显然是可以滴，本质也就是执行FFmpeg的命令行程序。