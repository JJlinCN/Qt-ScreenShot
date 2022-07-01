/*
 * author:huangyihonh
 * date:2022/6/28
*/
#include "share.h"
#include <QDesktopServices>
#include <QUrl>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>  //Qt封装好的打印机对话框
#include <cstdlib>
#include <QClipboard>
#include <QApplication>

Share::Share(QWidget *parent) : QWidget(parent){

    m_img.load("/temp/1.jpg");
}
void Share::shareToQQ()
{
    //启动系统中的qq
    system("qq");
    //将这个图片复制在全局剪贴板中，打开程序后可直接粘贴分享
    QApplication::clipboard()->setImage(m_img,QClipboard::Clipboard);
}

void Share::shareToWeXin()
{
    //调用桌面工具去访问这个网址
        QDesktopServices::openUrl(QUrl("https://wx.qq.com"));
   //将这个图片复制在全局剪贴板中，打开程序后可直接粘贴分享
        QApplication::clipboard()->setImage(m_img,QClipboard::Clipboard);
}

void Share::sendByEmail()
{

    QDesktopServices::openUrl(QUrl("https://mail.qq/com"));
    //将这个图片复制在全局剪贴板中，打开程序后可直接粘贴分享
    QApplication::clipboard()->setImage(m_img,QClipboard::Clipboard);
}

void Share::startPrint()
{
    QImage img;
    //加载出当前截取的图片
    img.load("/temp/1.jpg");

    //打印机
    QPrinter printer{QPrinter::ScreenResolution};
    QPrintDialog dialog{&printer};

    if(dialog.exec() == QDialog::Accepted){
        QPainter painter;
        painter.begin(&printer);

        //设置要绘画的范围,以一个矩形表示
        QRect rect = painter.viewport();
        //需要绘制的尺寸
        QSize size = img.size();

        //根据所能绘制的范围和需要绘制的图案大小来调整合适的打印尺寸
        size.scale(rect.size(),Qt::KeepAspectRatio); //打印的图片尺寸按照比例进行缩放
        //将painter的绘制区域设置为图片的大小区域
        painter.setViewport(rect.x(),rect.y(),rect.width(),rect.height());
        painter.setWindow(img.rect());
        painter.drawImage(0,0,img);//绘制参数中的这个图片

        //绘制完毕
        painter.end();

    }


}
