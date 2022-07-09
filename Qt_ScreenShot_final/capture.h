/*
author:huangyihong pengyueting longxinping
date:2022/6/29
*/
#ifndef CAPTURE_H
#define CAPTURE_H
#include<QMainWindow>
#include <QPixmap>
#include <iostream>

class ImageProvider;
class RectScreen;
class MyLabel;
class FreeCapture;
class Filter;
class Capture : public QMainWindow
{
Q_OBJECT

public:

    Capture(QMainWindow *parent = nullptr);
    std::string exec(const char *cmd);//使用exec函数对获取活动窗口id的命令做解析运行，返回运行结果
    ImageProvider *imageProvider;
signals:
    //以下两个信号都是c++端和qml端通信的信号
    void finishCapture();  //告诉qml截屏结束了
    void callImageChanged();  //有新的截屏产生，告知qml有新的图片截取下来
    void imageCopied();
//    void copyPaintImageSend(QImage providerImage);
public slots:
    void cutScreen(QPixmap capturePixmap); //将矩形截图和长截图的图片传递到qml中，并且复制
    void cutNull(); //没有截取屏幕，即退出了截屏
    QImage getImage();
    void setImage(QImage img);
    void startRectShot();
    void startActiveShot();
    void startFullShot();
    void startContinueShot();
    void copyToClipboard(QImage image); //将内容复制到剪切板
    void copyCurrentImageToClipboard();
    void startFreeShot();//不规则截图
    void nailedToTable(); //把图片钉在桌面上，是在矩形截图的默认功能下
    void cutNailScreen(QPixmap pixmap);//将钉在桌面上的图片显示出来。
    //filter 滤镜方法
    void filterRefresh(QImage img);
    void filterGrey();
    void filterOld();
    void filterWarm();
    void filterCool();
    void filterVague();
    void filterReverse();
    void filterSharpen();
    void filterSoften();
    void filterUndo();
    //保存图片
    void saveImage(QString savePath);
//    void copyPaintImage();
private:

RectScreen *m_rectScreenShot;
MyLabel *m_nailImage;
FreeCapture *m_freeScreenShot;
Filter *m_filter;
//int m_captureCount;
//QString m_path;
};

#endif // CAPTURE_H
