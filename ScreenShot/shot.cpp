//author:longxinping 2020051615040
//完成的功能：连续截图，全屏截图
//存在的问题：在截一张图后,截的图会被OK按钮覆盖，要把窗口拉大才会显示在窗口上
#include "shot.h"
#include<QScreen>
#include<QPainter>
#include<QPixmap>
#include<QApplication>
#include<vector>
#include<QTime>

Shot::Shot(QWidget *parent)
    : QMainWindow(parent)
{
    OK=new QPushButton("ok",this);
   // save=new QPushButton("save",this);
    //connect(OK,&QPushButton::clicked,this,&Shot::fullScreen);
    connect(OK,&QPushButton::clicked,[=](){
        fullScreen();
       // delete OK;
        //OK=nullptr;
    });
}
QString getTime()
{
    QTime time=QTime::currentTime();
    return time.toString();
}

void Shot::fullScreen()
{
//    QPixmap pixmap;
//    QScreen *screen=QApplication::primaryScreen();
//    pixmap=screen->grabWindow(0);

//    QImage img=pixmap.toImage();
//    img.save("/root/MyProject/1.jpg");
     time1=getTime();
    QScreen *screen=QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("/root/MyProject/"+time1+".jpg");
   // emit OK->cutScreen();
}

void Shot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap("/root/MyProject/"+time1+".jpg"),QRect());

}

Shot::~Shot()
{

}

