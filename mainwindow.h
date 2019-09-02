#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QtCore>

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <linux/v4l2-controls.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>


#include <stdbool.h>
#include <math.h>

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <iostream>

#include "thermometry.h"
#include "SimplePictureProcessing.h"

#define IMAGEWIDTH 384
#define IMAGEHEIGHT 292

#define TRUE 1
#define FALSE 0

#define FILE_VIDEO1 "/dev/video1"
using namespace xtherm;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    int init_v4l2(void);                    //初始化
    int v4l2_grab(void);                    //采集
    int v4l2_control(int);                  //控制
private slots:
    void on_btnImage_clicked();
    void on_btnVideo_clicked();
    void timerUpDate();
    void FpsUpDate();
    void timerVideo();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SimplePictureProcessing* mSimplePictureProcessing;
    unsigned char *buffer;                          //buffers 指针记录缓冲帧
    int fd;                          //设备描述符
    struct v4l2_streamparm setfps;          //结构体v4l2_streamparm来描述视频流的属性
    struct v4l2_capability cap;             //取得设备的capability，看看设备具有什么功能，比如是否具有视频输入,或者音频输入输出等
    struct v4l2_fmtdesc fmtdesc;            //枚举设备所支持的image format:  VIDIOC_ENUM_FMT
    struct v4l2_format fmt,fmtack;          //子结构体struct v4l2_pix_format设置摄像头采集视频的宽高和类型：V4L2_PIX_FMT_YYUV V4L2_PIX_FMT_YUYV
    struct v4l2_requestbuffers req;         //向驱动申请帧缓冲的请求，里面包含申请的个数
    struct v4l2_buffer buf;                 //代表驱动中的一帧
    enum   v4l2_buf_type type;              //帧类型
    struct v4l2_control ctrl;
    float temperatureTable[16384];
    float temperatureData[384*288];
    unsigned int fps;
    bool needRefreshTable;
    int delayy;
    Mat cvimg;
    QTimer *videoTimer;
    VideoWriter vw;
    VideoCapture cam;
};

#endif // MAINWINDOW_H
