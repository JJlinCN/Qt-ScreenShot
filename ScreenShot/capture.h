#ifndef CAPTURE_H
#define CAPTURE_H
#include<QMainWindow>
#include <QPixmap>
#include <iostream>

class ImageProvider;
class RectScreen;

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

public slots:
    void cutScreen(QPixmap capturePixmap);
    void cutNull();
    void startRectShot();
    void startActiveShot();
    void startFullShot();
    void copyToClipboard(QImage image);
private:

RectScreen *m_rectScreenShot;
//int m_captureCount;
//QString m_path;
};

#endif // CAPTURE_H
