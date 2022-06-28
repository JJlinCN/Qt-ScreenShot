#include <capture.h>
#include <QApplication>
#include <QScreen>
#include "RecScreen.h"
#include "freecapture.h"
#include "imgprovider.h"
#include "mylabel.h"
#include "filter.h"
#include <KWindowSystem>
#include <QDebug>

Capture::Capture(QMainWindow *parent):QMainWindow(parent)/*,m_captureCount{0}*//*,m_path{"/temp/"}*/{

    imageProvider = new ImageProvider;
    m_filter = new Filter;//所有滤镜操作应共享一个滤镜器及其资源,每次截取会把截取到的图片设置为滤镜器的初始图片，滤镜则是复制一份初始图片进行修改，方便回退初始图片undo
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
    m_filter->setFilterImage(imageProvider->image);

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
    m_filter->setFilterImage(imageProvider->image);//设置滤镜初始图片为缓存图片
}

void Capture::copyToClipboard(QImage image){
   // QImage image = capturePixmap.toImage();
    QApplication::clipboard()->clear();
    QApplication::clipboard()->setImage(image,QClipboard::Clipboard);
    emit imageCopied();
}

void Capture::copyCurrentImageToClipboard(){
    copyToClipboard(imageProvider->image);
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
    m_filter->setFilterImage(imageProvider->image);//将截取到的图片作为滤镜器的起始图片
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
    m_filter->setFilterImage(imageProvider->image);
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

void Capture::startFreeShot(){
    m_freeScreenShot = new FreeCapture;
    connect(m_freeScreenShot,&FreeCapture::signalCompleteCapture,this,&Capture::cutScreen);
    m_freeScreenShot->show();
}

void Capture::filterRefresh(QImage img){
    imageProvider->image=img;
    emit callImageChanged();//刷新图片
}

void Capture::filterGrey(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->grey();
}

void Capture::filterOld(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->old();
}

void Capture::filterWarm(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->warm();
}

void Capture::filterCool(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->cool();
}

void Capture::filterVague(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->vague();
}

void Capture::filterReverse(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->reverse();
}

void Capture::filterSharpen(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->sharpen();
}

void Capture::filterSoften(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->soften();
}

void Capture::filterUndo(){
    connect(m_filter,&Filter::sendFilterImage,this,&Capture::filterRefresh);
    m_filter->undo();
}

void Capture::saveImage(QString savePath){
    imageProvider->image.save(savePath);
    qDebug()<<savePath;
}
