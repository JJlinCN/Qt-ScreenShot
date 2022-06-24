#include "mylabel.h"
#include <QMouseEvent>
#include <QPoint>

MyLabel::MyLabel(QLabel *parent):QLabel(parent),m_point{0,0}{

    this->setScaledContents(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //将这个组件提升到栈顶，可以实现就算关闭主窗口，也不会将钉在桌面上的截图一起销毁，双击才能销毁。
    this->raise();
}


void MyLabel::mousePressEvent(QMouseEvent *event){

    QPoint globalPos = event->globalPosition().toPoint();
    QPoint point = this->geometry().topLeft();
    m_point = globalPos - point;
}

void MyLabel::mouseMoveEvent(QMouseEvent *event){

    QPoint global = event->globalPosition().toPoint();
    QPoint point  = global - m_point;
    this->move(point);
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event){

    Q_UNUSED(event);
    //鼠标释放，之前按下的点清零
    m_point = QPoint(0,0);
}

void MyLabel::wheelEvent(QWheelEvent *event)
{
    //为定在桌面上的图片添加滚轮放缩事件
    QPoint point = event->angleDelta();
    int stept{0};
    auto imageWidth = this->width();
    auto imageHeight  = this->height();
    if(!point.isNull()){
        //调整放缩的步调，让过程更平缓
        stept = point.y()/3;
        this->resize(imageWidth + stept,imageHeight + stept);
    }
}

void MyLabel::mouseDoubleClickEvent(QMouseEvent *event){

    //label受到双击事件，销毁钉在桌面上的图片窗口
    Q_UNUSED(event);
    this->destroy(true,true);
}
