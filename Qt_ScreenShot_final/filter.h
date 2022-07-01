//pengyueting 2020051615252
#ifndef FILTER_H
#define FILTER_H
//#include"mosaic.h"
#include <QWidget>

class Filter : public QWidget
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = nullptr);

    void coolImage(int delta);
    void warmImage(int delta);
    void setFilterImage(QImage img);
    friend class Capture;
private:
    void grey();
    void old();
    void warm();
    void cool();
    void vague();
    void reverse();
    void sharpen();
    void soften();
    void undo();
signals:
    void sendFilterImage(QImage img);//接收image,将filter内存栈中img利用信号传递出去

private:
    QImage m_ImageStart;//转换前
    QImage m_ImageFinal;//转换后
};
#endif // FILTER_H
