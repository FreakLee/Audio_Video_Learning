#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <thread>

//输入格式
#define INPUT_FMT "avfoundation"
//设备名字
#define DEVICE_NAME ":0"
//输出文件名字
#warning 请修改这里
#define OUTPUT_FILE_NAME "/Users/你的电脑用户名/Desktop/output.wav"

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/time.h>
}


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

