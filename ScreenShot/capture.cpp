#include <capture.h>
#include <QApplication>
#include <QScreen>
#include "RecScreen.h"
#include "imgprovider.h"
#include "mylabel.h"
#include <KWindowSystem>
#include <QDebug>

Capture::Capture(QMainWindow *parent):QMainWindow(parent)/*,m_captureCount{0}*//*,m_path{"/temp/"}*/{

    imageProvider = new ImageProvider;
}
std::string Capture::exec(const char *cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

void Capture::startActiveShot()
{

    //得到窗口的wid,string类型的16进制
    std::string  string=exec(" xprop -root | awk '/_NET_ACTIVE_WINDOW\\(WINDOW\\)/{print $NF}'").c_str();
 const char *c=string.data();
    char *stop;
    WId id=std::strtol(c,&stop,16);

    qDebug()<<"窗口ID："<<id;
//    WId id = KWindowSystem::activeWindow();
//    qDebug()<<id;
    QPixmap pixmap;
    QScreen *screen=QApplication::primaryScreen();

    this->setCursor(Qt::ArrowCursor);  //显示正常鼠标
    pixmap=screen->grabWindow(id);
    imageProvider->image=pixmap.toImage();

   // QImage img=pixmap.toImage();

   // m_captureCount ++ ;
   // QString path = m_path + QString("%1.jpg").arg(m_captureCount);
   // img.save(path);

    //发送信号 将形截取的图片在姐妹显示
    emit callImageChanged();
    //发送信号 告知qml矩形截屏结束
    emit finishCapture();
}

void Capture::startFullShot()
{
    QPixmap pixmap;
    QScreen *screen=QApplication::primaryScreen();//获得当前主屏幕
    pixmap=screen->grabWindow(0);  //参数为0,抓取整个屏幕
    QImage img=pixmap.toImage();
    imageProvider->image = img;  //将抓取到的图片提供给qml
    copyToClipboard(img);
    emit callImageChanged();
    emit finishCapture();
    //img.save("/root/MyProject/1.jpg");

}

void Capture::copyToClipboard(QImage image){
   // QImage image = capturePixmap.toImage();
    QApplication::clipboard()->clear();
    QApplication::clipboard()->setImage(image,QClipboard::Clipboard);
    emit imageCopied();
}

void Capture::nailedToTable()
{
   m_rectScreenShot = new RectScreen();
   connect(m_rectScreenShot,&RectScreen::signalCompleteCapture,this,&Capture::cutNailScreen);
   m_rectScreenShot->show();
}

void Capture::cutNailScreen(QPixmap pixmap)
{
    //QImage image = pixmap.toImage()
    imageProvider->image = pixmap.toImage();
    //image.save();
    m_nailImage = new MyLabel();
    m_nailImage->setPixmap(pixmap);

    m_nailImage->show();

    emit callImageChanged();
    emit finishCapture();
}

void Capture::cutScreen(QPixmap capturePixmap){

    QImage image = capturePixmap.toImage();
    imageProvider->image=image;
    copyToClipboard(image);
    //m_captureCount ++ ;
    //QString path = m_path + QString("%1.jpg").arg(m_captureCount);
   // image.save(path);
    emit finishCapture();
    emit callImageChanged();
}

void Capture::cutNull(){
    emit finishCapture();
}

void Capture::startRectShot(){
    m_rectScreenShot = new RectScreen;
    connect(m_rectScreenShot,&RectScreen::signalCompleteCapture,this,&Capture::cutScreen);
    connect(m_rectScreenShot,&RectScreen::nullCapture,this,&Capture::cutNull);
    m_rectScreenShot->show();
}
