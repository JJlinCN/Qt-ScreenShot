/*author:huangyihong
    date:2022/6/28
*/
#ifndef ELEMENTGROUP_H
#define ELEMENTGROUP_H
#include<QQuickPaintedItem>
#include "edit.h"
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QRectF>
#include <iostream>

class TextElement{

//编辑中的文字编辑元素
public:
    TextElement(){};
    TextElement(const QPen &framePen,QPen &textPen,int textFont/*,QString content*/):m_framePen{framePen},m_textPen{textPen},/*m_content{content},*/m_font{textFont}{

    }

    //文本编辑
    Text *myText;
   // QRect m_frame;

    //文字矩形框的开始点
    QPoint m_startPoint;
    //文字矩形框的结束点
    std::vector<QPoint> m_endPoints;

    //文字框的画笔
    QPen m_framePen;

    //里面文字内容的画笔
    QPen m_textPen;

    //里面的文字内容
//    QString m_content;

    //文字大小
    int m_font;
};

class CircleElement{

    //椭圆编辑框
public:
    CircleElement(){};
    CircleElement(QPen pen,bool isFill ):m_pen{pen},m_isFill{isFill}{};

    //框的画笔
    QPen m_pen;

    //生成这个椭圆的矩形原型开始点
    QPoint m_startPoint;

    //结束点
    std::vector<QPoint> m_endPoints;

    //这个椭圆是否需要被填充
    bool m_isFill;
};

class RectElement{

public:
    QPoint m_startPoint;
    std::vector<QPoint> m_endPoints;
    bool m_isFill;
    QPen m_pen;
    RectElement(){};
    RectElement(QPen &pen,bool isFill):m_isFill{isFill},m_pen{pen}{};

};

class LineElement{
    //直线元素
public:
    QPen m_pen;
    QPoint m_startPoint;
    std::vector<QPoint> m_endPoints;
    LineElement(){};
    LineElement(QPen pen):m_pen{pen}{};

};

//截取矩形，装的是每次截取的矩形
class CutRectElement{
public:
    QRectF m_cutRect;

    CutRectElement(){};

    CutRectElement(const QRectF &rect):m_cutRect{rect}{};
};

//涂鸦类
class DoodleElement{

public:
    QVector<QLineF> m_lines;
    QPen m_pen;

    DoodleElement(){};  //构造函数

    DoodleElement(QPen &pen):m_pen{pen}{};

    DoodleElement(const DoodleElement &doodle){
        m_lines = doodle.m_lines;
        m_pen = doodle.m_pen;
    }

    //操作符重载
    DoodleElement &operator=(const DoodleElement &doodle){

        if(&doodle != this){
            this->m_lines = doodle.m_lines;
            this->m_pen = doodle.m_pen;
        }
        return *this;
    }
};

#endif // ELEMENTGROUP_H
