/*
author:huangyihong
date:2022/6/29
*/
#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>

class MyLabel :public QLabel{
public:

    MyLabel(QLabel *parent = nullptr);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    QPoint m_point;

};

#endif // MYLABEL_H
