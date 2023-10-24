## 命令行工具

FFmpeg的bin目录下有三个工具，可在终端直接输入命令执行

* [ffmpeg](https://ffmpeg.org/ffmpeg.html)是一个通用的媒体转换器。它可以读取各种输入，包括实时抓取/录制设备-过滤，并将它们转码为多种输出格式。
* [ffplay](https://ffmpeg.org/ffplay.html)是一款基于 FFmpeg 库和 SDL 库的简单媒体播放器。它主要用作各种FFmpeg API的测试平台。
* [ffprobe](https://ffmpeg.org/ffprobe.html)是一个多媒体分析器，并以人类和机器可读的方式打印出从多媒体中收集的信息。

## ffmpeg命令

终端直接输入ffmpeg，可以获得用法提示

``` sh
usage: ffmpeg [options] [[infile options] -i infile]... {[outfile options] outfile}...

Use -h to get full help or, even better, run 'man ffmpeg'
```

可以看到它有5个参数，简化一下就是：ffmpeg {1} {2} -i {3} {4} {5}，5个参数含义分别如下：

* 全局参数
* 输入文件参数
* 输入文件
* 输出文件参数
* 输出文件

详细用法可以查阅官方文档，或者查阅man page，或者输入下面命令查阅说明：

* ffmpeg -h：简易版说明
* ffmpeg -h long：详细版说明
* ffmpeg -h full：完整版说明

部分参数解释：

* -i input_file：指定输入文件的路径和名称。
示例：-i input.mp4

* -ss position：指定从输入文件的哪个时间位置开始处理，格式为HH:MM:SS.xxx（小时:分钟:秒.毫秒）。
示例：-ss 00:01:30.500 表示从1分30.5秒开始处理。

* -t duration：指定处理的持续时间，格式为HH:MM:SS.xxx（小时:分钟:秒.毫秒）。
示例：-t 00:00:45 表示处理45秒的内容。

* -vf filtergraph：指定视频过滤器图形，用于对视频进行各种处理，如调整大小、裁剪、旋转、滤镜等。
示例：-vf "scale=640:480" 表示将视频调整为640x480的大小。

* -af filtergraph：指定音频过滤器图形，用于对音频进行各种处理，如音频增益、降噪、混音等。
示例：-af "volume=2.0" 表示将音频增益调整为原来的2倍。

* -c:v codec：指定视频编解码器。
示例：-c:v libx264 表示使用libx264编码器进行视频编码。

* -c:a codec：指定音频编解码器。
示例：-c:a aac 表示使用AAC编码器进行音频编码。

* -b:v bitrate：指定视频的比特率，即视频的质量。较高的比特率通常意味着更好的视频质量，但文件大小也会增加。
示例：-b:v 1000k 表示视频比特率为1000kbps。

* -b:a bitrate：指定音频的比特率，即音频的质量。较高的比特率通常意味着更好的音频质量，但文件大小也会增加。
示例：-b:a 128k 表示音频比特率为128kbps。

* -r framerate：指定视频的帧率，即每秒播放的画面数量。较高的帧率可以获得更流畅的视频，但也会增加文件大小。
示例：-r 30 表示视频帧率为30帧每秒。

### 查看设备

``` sh
ffmpeg -devices
```

当前电脑输出的可用设备如下：

``` sh
Devices:
 D. = Demuxing supported
 .E = Muxing supported
 --
  E audiotoolbox    AudioToolbox output device
 D  avfoundation    AVFoundation input device
 D  lavfi           Libavfilter virtual input device
  E sdl,sdl2        SDL2 output device
 D  x11grab         X11 screen capture, using XCB
```

在多媒体处理中，"demuxer"（解封装器）和"muxer"（封装器）是两个常用的概念，用于描述多媒体文件的解封装和封装操作。

1、**Demuxer（解封装器）** 是一个用于将多媒体文件（如音频或视频文件）解封装为原始音频流、视频流和其他相关数据的组件。它读取多媒体文件的容器格式（如MP4、AVI、MKV）并解析其中的音频、视频和其他流，将它们提供给后续处理的组件（如解码器）进行解码和处理。Demuxer将多媒体文件中的不同媒体流分离开来，以便进行独立的处理。

2、**Muxer（封装器）** 是一个用于将音频流、视频流和其他相关数据封装到容器格式中的组件。它接收来自解码器或其他处理组件的音频流、视频流等数据，并将它们合并到指定的容器格式中（如MP4、AVI、MKV），生成一个包含音视频数据的完整多媒体文件。Muxer负责将不同的音频和视频流合并，并添加必要的容器元数据和索引信息。

AVFoundation 对于iOS开发者来说再熟悉不过了，输入如下命令可以查看支持avfoundation支持的设备：

``` sh
ffmpeg -f avfoundation -list_devices true -i ''
```

输出结果如下：
``` sh
[AVFoundation indev @ 0x7fd0621043c0] AVFoundation video devices:
[AVFoundation indev @ 0x7fd0621043c0] [0] FaceTime HD Camera (Built-in)
[AVFoundation indev @ 0x7fd0621043c0] [1] Capture screen 0
[AVFoundation indev @ 0x7fd0621043c0] AVFoundation audio devices:
[AVFoundation indev @ 0x7fd0621043c0] [0] Built-in Microphone
```

对于Windows平台则是查看dshow（DirectShow）输入支持的设备：
``` sh
ffmpeg -f dshow -list_devices true -i dummy
```

使用以下命令查看FFmpeg是否支持特定设备：
``` sh
ffmpeg -sources DEVICE
```
其中，DEVICE是要查询的设备名称，例如alsa、pulse、v4l2等。

### 音频处理

1、**录制音频**
在Mac OS使用FFmpeg录制音频，可以使用如下命令：

``` sh
ffmpeg -f avfoundation -i ":0" output.wav
```

这个命令使用了FFmpeg的avfoundation输入设备，从Mac的音频输入设备（通常是麦克风）录制音频。":0"参数表示默认的音频输入设备，output.wav是要保存音频的文件名和格式。可以将其更改为所需的文件名和扩展名。

执行命令后，FFmpeg将开始录制音频，并在后台显示进度信息。要停止录制，可以按下Ctrl+C。

2、**查看音频信息**
``` sh
ffmpeg -i output.wav
```
输出结果如下：

``` sh
Input #0, wav, from 'output.wav':
  Metadata:
    encoder         : Lavf60.3.100
  Duration: 00:00:19.56, bitrate: 1411 kb/s
  Stream #0:0: Audio: pcm_s16le ([1][0][0][0] / 0x0001), 44100 Hz, 2 channels, s16, 1411 kb/s
```

当然，该命令也可以查看视频文件信息，例如查看前几天在YouTube上下载的一个视频信息：

``` sh
Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'test.mp4':
  Metadata:
    major_brand     : mp42
    minor_version   : 0
    compatible_brands: isommp42
    creation_time   : 2023-10-13T02:00:12.000000Z
  Duration: 00:12:11.92, start: 0.000000, bitrate: 1134 kb/s
  Stream #0:0[0x1](und): Video: h264 (High) (avc1 / 0x31637661), yuv420p(tv, bt709, progressive), 1280x720 [SAR 1:1 DAR 16:9], 1003 kb/s, 30 fps, 30 tbr, 15360 tbn (default)
    Metadata:
      creation_time   : 2023-10-13T02:00:12.000000Z
      handler_name    : ISO Media file produced by Google Inc. Created on: 10/12/2023.
      vendor_id       : [0][0][0][0]
  Stream #0:1[0x2](eng): Audio: aac (LC) (mp4a / 0x6134706D), 44100 Hz, stereo, fltp, 128 kb/s (default)
    Metadata:
      creation_time   : 2023-10-13T02:00:12.000000Z
      handler_name    : ISO Media file produced by Google Inc. Created on: 10/12/2023.
      vendor_id       : [0][0][0][0]
```

3、**提取音频**

比如，从上面的test.mp4视频中提取音频：

``` sh
ffmpeg -i test.mp4 -vn test.mp3
```

-vn表示去除视频流，处理信息如下：

``` sh
Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'test.mp4':
  Metadata:
    major_brand     : mp42
    minor_version   : 0
    compatible_brands: isommp42
    creation_time   : 2023-10-13T02:00:12.000000Z
  Duration: 00:12:11.92, start: 0.000000, bitrate: 1134 kb/s
  Stream #0:0[0x1](und): Video: h264 (High) (avc1 / 0x31637661), yuv420p(tv, bt709, progressive), 1280x720 [SAR 1:1 DAR 16:9], 1003 kb/s, 30 fps, 30 tbr, 15360 tbn (default)
    Metadata:
      creation_time   : 2023-10-13T02:00:12.000000Z
      handler_name    : ISO Media file produced by Google Inc. Created on: 10/12/2023.
      vendor_id       : [0][0][0][0]
  Stream #0:1[0x2](eng): Audio: aac (LC) (mp4a / 0x6134706D), 44100 Hz, stereo, fltp, 128 kb/s (default)
    Metadata:
      creation_time   : 2023-10-13T02:00:12.000000Z
      handler_name    : ISO Media file produced by Google Inc. Created on: 10/12/2023.
      vendor_id       : [0][0][0][0]
Stream mapping:
  Stream #0:1 -> #0:0 (aac (native) -> mp3 (libmp3lame))
Press [q] to stop, [?] for help
Output #0, mp3, to 'test.mp3':
  Metadata:
    major_brand     : mp42
    minor_version   : 0
    compatible_brands: isommp42
    TSSE            : Lavf60.3.100
  Stream #0:0(eng): Audio: mp3, 44100 Hz, stereo, fltp (default)
    Metadata:
      creation_time   : 2023-10-13T02:00:12.000000Z
      handler_name    : ISO Media file produced by Google Inc. Created on: 10/12/2023.
      vendor_id       : [0][0][0][0]
      encoder         : Lavc60.3.100 libmp3lame
size=   11437kB time=00:12:11.89 bitrate= 128.0kbits/s speed=58.3x
video:0kB audio:11437kB subtitle:0kB other streams:0kB global headers:0kB muxing overhead: 0.002946%
```

4、**转换音频格式**

将上面的output.wav转换成output.mp3：

``` sh
ffmpeg -i output.wav -c:a libmp3lame output.mp3
```

5、**调整音频音量**

将上面的output.mp3调成2倍音量并保存为output_dvolume.mp3：

``` sh
ffmpeg -i output.mp3 -af "volume=2.0" output_dvolume.mp3
```

6、**合并音频**

将上面的output.mp3与output_dvolume.mp3两个音频文件合并成一个新的音频文件并保存merge_output.mp3：

``` sh
ffmpeg -i output.mp3 -i output_dvolume.mp3 -filter_complex "[0:a][1:a]concat=n=2:v=0:a=1[out]" -map "[out]" merge_output.mp3
```

7、**剪切音频**

从输入文件test.mp3中剪切出从1分30秒到2分30秒的部分，并保存为test_cut.mp3：

``` sh
ffmpeg -i test.mp3 -ss 00:01:30 -to 00:02:30 -c copy test_cut.mp3
```

-c copy表示不改变音频和视频的编码格式，直接拷贝，提升效率

8、**添加音频效果**

将对输入文件test_cut.mp3应用音频效果，包括加速2倍(atempo)、高通滤波器(highpass)和低通滤波器(lowpass)，并保存为test_cut_ahl.mp3：

``` sh
ffmpeg -i test_cut.mp3 -af "atempo=2.0, highpass=f=200, lowpass=f=3000" test_cut_ahl.mp3
```

9、**添加封面**

``` sh
ffmpeg -i test.mp3 -i test.jpeg -map 0 -map 1 -c copy -id3v2_version 3 -metadata:s:v title="Album cover" -metadata:s:v comment="Cover (Front)" test_cover.mp3
```

从test.mp3音频文件中提取音频流，并从test.jpeg图像文件中提取封面图像。然后，它将使用-map选项将音频流和封面图像流映射到输出文件。-c copy选项用于直接复制音频流和封面图像流，而不进行重新编码。-id3v2_version 3选项用于设置ID3标签版本为3，以确保兼容性。-metadata:s:v选项用于指定封面图像的元数据，如标题和注释。

添加封面后，文件变大了，这是意料之中的。下面的打印信息中也可表明标题和注释添加成功了。

``` sh
Input #0, mp3, from 'test_cover.mp3':
  Metadata:
    major_brand     : mp42
    minor_version   : 0
    compatible_brands: isommp42
    encoder         : Lavf60.3.100
  Duration: 00:12:11.95, start: 0.025056, bitrate: 129 kb/s
  Stream #0:0: Audio: mp3, 44100 Hz, stereo, fltp, 128 kb/s
    Metadata:
      encoder         : Lavc60.3.
  Stream #0:1: Video: mjpeg (Baseline), yuvj420p(pc, bt470bg/unknown/unknown), 1024x1024 [SAR 96:96 DAR 1:1], 90k tbr, 90k tbn (attached pic)
    Metadata:
      title           : Album cover
      comment         : Cover (front)
```

### 视频处理

视频有很多跟音频类似的处理操作，这里只简单列举几种用法，更多用法需要时再查阅文档。

1、**录制视频**

``` sh
ffmpeg -f avfoundation -i “1:0” out.avi
```
将视频设备1中的视频和音频设备0中的音频录制到out.avi

2、**视频转码**

``` sh
ffmpeg -i out.avi out.mp4
```
将视频out.avi转为out.mp4

3、**视频截图**

``` sh
ffmpeg -i out.mp4 -ss 00:00:10 -vframes 1 output.jpg
```
从上面的out.mp4中提取第10秒的视频帧，并将其保存为输出文件output.jpg。参数`-vframes 1`表示只提取一帧。

## ffplay命令

其实，在上面音视频的处理过程中，经常用到了ffplay命令，以测试一部分音视频处理是否成功。相比ffmpeg命令，ffplay就简单多了。

``` sh
ffplay [options] [input_url]
```

这个命令会打开一个窗口，并播放指定的输入文件。常用的参数：

* -i input_file：指定输入文件的路径和名称。

* -ss position：指定从输入文件的哪个时间位置开始播放，格式为HH:MM:SS.xxx（小时:分钟:秒.毫秒）。

* -t duration：指定播放的持续时间，格式为HH:MM:SS.xxx（小时:分钟:秒.毫秒）。

* -vf filtergraph：指定视频过滤器图形，用于对视频进行各种处理，如调整大小、裁剪、旋转、滤镜等。

* -af filtergraph：指定音频过滤器图形，用于对音频进行各种处理，如音频增益、降噪、混音等。

* -volume volume：指定播放音量的大小，取值范围为0.0到1.0。

* -nodisp：禁用显示窗口，只进行音频的播放。

* -an：禁用音频播放。

* -vn：禁用视频播放。

* -stats：显示播放统计信息，如帧率、比特率等。

* -loop n：循环播放输入文件n次。

也可以使用键盘上的一些快捷键进行控制，例如：

* 空格键：暂停/恢复播放。
* 左方向键：后退10秒。
* 右方向键：快进10秒。
* 上方向键：增加音量。
* 下方向键：减小音量。
* q键：退出播放。

## ffprobe命令
ffprobe是FFmpeg提供的一个命令行工具，用于分析媒体文件的详细信息。它可以提供音视频流的元数据、编解码器信息、时长、帧率等数据。语法如下：

``` sh
ffprobe [options] input_url
```

常用的参数：

* -i input_file：指定输入文件的路径和名称。

* -show_format：显示媒体文件的格式信息。

* -show_streams：显示媒体文件中的音视频流信息。

* -show_packets：显示媒体文件中的数据包信息。

* -show_frames：显示媒体文件中的帧信息。

* -show_programs：显示媒体文件中的节目信息。

* -show_chapters：显示媒体文件中的章节信息。

* -show_data：显示媒体文件中的数据信息。

* -show_error：显示错误信息。

* -of format：指定输出格式，默认为default。可以选择的输出格式有default、json、xml、csv等。

* -select_streams stream_specifier：选择特定的音视频流进行分析。stream_specifier可以是a（音频流）、v（视频流）、s（字幕流）等。

* -sexagesimal：以时分秒格式显示时间相关信息。

* -count_frames：计算媒体文件中的帧数。

* -count_packets：计算媒体文件中的数据包数。

简单举个例子，ffprobe -show_format out.mp4，输出部分信息如下：

``` sh
filename=out.mp4
nb_streams=2
nb_programs=0
format_name=mov,mp4,m4a,3gp,3g2,mj2
format_long_name=QuickTime / MOV
start_time=0.000000
duration=23.966667
size=18413363
bit_rate=6146324
probe_score=100
TAG:major_brand=isom
TAG:minor_version=512
TAG:compatible_brands=isomiso2avc1mp41
TAG:encoder=Lavf60.3.100
```

## 参考

[1、官网文档](https://ffmpeg.org/documentation.html)
[2、阮一峰FFmpeg视频处理入门教程](https://ruanyifeng.com/blog/2020/01/ffmpeg.html)
[3、FFMPEG ENCODING AND EDITING COURSE](https://slhck.info/ffmpeg-encoding-course/)
