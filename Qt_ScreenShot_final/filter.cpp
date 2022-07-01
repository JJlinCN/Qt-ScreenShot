//pengyueting 2020051615252
#include "filter.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <QFileDialog>

Filter::Filter(QWidget *parent) :
    QWidget(parent)
{
    update();

    setWindowTitle("滤镜");

    //m_Image.load("/root/MyProject/2.jpg");
}

void Filter::coolImage(int delta)
{
    m_ImageFinal = m_ImageStart.copy();//深拷贝

    int r,g,b;
    QColor frontColor;
    for(int x=0; x<m_ImageFinal.width(); x++){
        for(int y=0; y<m_ImageFinal.height(); y++){
            frontColor = QColor(m_ImageStart.pixel(x,y));

            r = frontColor.red();
            g = frontColor.green();
            b = frontColor.blue()+delta;

            //we check if the new value is between 0 and 255
            b = qBound(0, b, 255);

            m_ImageFinal.setPixel(x,y, qRgb(r,g,b));
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal); //将修改后的图片发送出去
}

void Filter::warmImage(int delta)
{
    QImage m_ImageFinal = m_ImageStart.copy();

    int r,g,b;
    QColor frontColor;
    for(int x=0; x<m_ImageFinal.width(); x++){
        for(int y=0; y<m_ImageFinal.height(); y++){
            frontColor = QColor(m_ImageStart.pixel(x,y));

            r = frontColor.red()+delta;
            g = frontColor.green()+delta;
            b = frontColor.blue();

            //we check if the new value is between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0,g,255);

            m_ImageFinal.setPixel(x,y, qRgb(r,g,b));
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

//灰度
void Filter::grey()
{
    //    m_Image.load("/root/images/04.jpg");
    m_ImageFinal = m_ImageStart.copy();
    for (int i = 0; i < m_ImageStart.width(); i++)
    {
        for (int j = 0; j < m_ImageStart.height(); j++)
        {
            QColor oriColor = m_ImageStart.pixel(i, j);
            int average = (oriColor.red() + oriColor.green() + oriColor.blue()) / 3;
            oriColor = QColor(average, average, average);
            m_ImageFinal.setPixelColor(i, j, oriColor);
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

//老照片
void Filter::old()
{
    m_ImageFinal = m_ImageStart.copy();

    QColor frontColor;
    for(int x=0; x<m_ImageFinal.width(); x++){
        for(int y=0; y<m_ImageFinal.height(); y++){
            frontColor = QColor(m_ImageStart.pixel(x,y));

            int r = 0.393 * frontColor.red() + 0.769 * frontColor.green() + 0.189 * frontColor.blue();
            int g = 0.349 * frontColor.red() + 0.686 * frontColor.green() + 0.168 * frontColor.blue();
            int b = 0.272 * frontColor.red() + 0.534 * frontColor.green() + 0.131 * frontColor.blue();
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            m_ImageFinal.setPixel(x,y, qRgb(r,g,b));
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

//暖调
void Filter::warm()
{
    warmImage(30);
}

//冷调
void Filter::cool()
{
    coolImage(50);
}

//模糊
void Filter::vague()
{
//    mosaic();
    int kernel [5][5]= {{0,0,1,0,0},
                        {0,1,3,1,0},
                        {1,3,7,3,1},
                        {0,1,3,1,0},
                        {0,0,1,0,0}};
    int kernelSize = 5;
    int sumKernel = 27;
    int r,g,b;
    QColor color;

    m_ImageFinal = m_ImageStart.copy();
    for(int x=kernelSize/2; x<m_ImageFinal.width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<m_ImageFinal.height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(m_ImageStart.pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            m_ImageFinal.setPixel(x,y, qRgb(r,g,b));
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

//反色
void Filter::reverse()
{
    m_ImageFinal = m_ImageStart.copy();

    int r,g,b;
    QColor frontColor;
    for(int x=0; x<m_ImageFinal.width(); x++){
        for(int y=0; y<m_ImageFinal.height(); y++){
            frontColor = QColor(m_ImageStart.pixel(x,y));

            r = frontColor.red();
            g = frontColor.green();
            b = frontColor.blue();

            m_ImageFinal.setPixel(x,y, qRgb(255-r,255-g,255-b));
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

//锐化
void Filter::sharpen()
{
    int kernel [3][3]= {{0,-1,0},
                        {-1,5,-1},
                        {0,-1,0}};
    int kernelSize = 3;
    int sumKernel = 1;
    int r,g,b;
    QColor color;

    m_ImageFinal = m_ImageStart.copy();
    for(int x=kernelSize/2; x<m_ImageFinal.width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<m_ImageFinal.height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(m_ImageFinal.pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            m_ImageFinal.setPixel(x,y, qRgb(r,g,b));

        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

//柔化
void Filter::soften()
{

    m_ImageFinal = m_ImageStart.copy();
    int r,g,b;
    QRgb color;
    for(int x=1; x<m_ImageFinal.width()-1; x++){
        for(int y=1; y<m_ImageFinal.height()-1; y++){
            r = 0; g = 0; b = 0;
            for(int m = 0; m < 9; m++)
            {
                int s = 0;
                int p = 0;
                switch(m){
                    case 0: s = x - 1;  p = y - 1;  break;
                    case 1: s = x;  p = y - 1;  break;
                    case 2: s = x + 1 ;  p = y -1;  break;
                    case 3: s = x + 1;  p = y ;  break;
                    case 4: s = x + 1;  p = y + 1;  break;
                    case 5: s = x;  p = y + 1;  break;
                    case 6: s = x - 1;  p = y + 1;  break;
                    case 7: s = x - 1;  p = y ;  break;
                    case 8: s = x;  p = y;  break;
                }
                color = m_ImageFinal.pixel(s, p);
                r += qRed(color);
                g += qGreen(color);
                b += qBlue(color);
            }

            r = (int) (r / 9.0);
            g = (int) (g / 9.0);
            b = (int) (b / 9.0);

            r = qMin(255, qMax(0, r));
            g = qMin(255, qMax(0, g));
            b = qMin(255, qMax(0, b));

            m_ImageFinal.setPixel(x, y, qRgb(r, g, b));
        }
    }
    update();
    emit sendFilterImage(m_ImageFinal);
}

void Filter::setFilterImage(QImage img){
    m_ImageStart = img.copy();
}

void Filter::undo(){
    m_ImageFinal = m_ImageStart.copy(m_ImageStart.rect());//将初始截取图片的深拷贝给修改后图片
    emit sendFilterImage(m_ImageFinal);
}
