/*
author:huangyihong pengyueting longxinping
date:2022/6/30
*/

#ifndef ELEMENTGROUP_H
#define ELEMENTGROUP_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QRectF>


//在二次开发中，我们将一个集合装所有结束点变为只有一个结束点，因为最终需要的都是最后的那一个结束点
//文字编辑
class TextElement
{
public:
    //构造函数
    TextElement(){}

    TextElement(const QPen &recPen,const QPen &textPen,const int &textFont,const QString &text)
        :m_text(text),m_recPen(recPen),m_textPen(textPen),m_font(textFont)
    {}

    //我们想使用QTextEdit来表示文本框的文本编辑部分
    //QTextEdit m_edit;
    //矩形区域的起始点
    QPoint m_startPoint;
    //矩形区域的终止点，用vector容器装可以确保当鼠标移动时，矩形区域也随之移动
//    std::vector<QPoint> m_endPoints;
    QPoint m_endPoint;
    //矩形区域的文本
    QString m_text;
    //矩形边框的画笔
    QPen m_recPen;
    //文字的画笔
    QPen  m_textPen;
    //文字的宽度
    int m_font;
};

//椭圆形
class CircleElement{
public:
    CircleElement(){}
    CircleElement(const QPen& pen,const bool isFill):
        m_pen(pen),
        m_isFill(isFill)
    {}
    //椭圆型区域的起始点
    QPoint m_startPoint;
    //椭圆型区域的终止点，用vector容器装可以确保当鼠标移动时，椭圆型区域也随之移动
//    std::vector<QPoint> m_endPoints;
    QPoint m_endPoint;
    //椭圆边框的画笔
    QPen m_pen;
    //是否要填充颜色
    bool m_isFill;
};

//矩形
class RectElement{
public:
    RectElement(){}
    RectElement(const QPen &pen,const bool isFill):
        m_pen(pen),
        m_isFill(isFill)
    {}

    //矩形区域的起始点
    QPoint m_startPoint;
    //矩形区域的终止点，用vector容器装可以确保当鼠标移动时，矩形区域也随之移动
//    std::vector<QPoint> m_endPoints;
    QPoint m_endPoint;
    //矩形边框的画笔
    QPen m_pen;
    //是否要填充颜色
    bool m_isFill;
};

////马赛克
//class MosaicElement{
//public:
//    MosaicElement(){}
//    MosaicElement(const QPen &pen,const bool isFill):
//        m_pen(pen),
//        m_isFill(isFill)
//    {}

//    //矩形区域的起始点
//    QPoint m_startPoint;
//    //矩形区域的终止点，用vector容器装可以确保当鼠标移动时，矩形区域也随之移动
////    std::vector<QPoint> m_endPoints;
//    QPoint m_endPoints;
//    //矩形边框的画笔
//    QPen m_pen;
//    //是否要填充颜色
//    bool m_isFill;
//};

//直线
class LineElement{
public:
    LineElement(){}
    LineElement(const QPen &pen):
        m_pen(pen)
    {}
    //直线的起始点
    QPoint m_startPoint;
    //直线的终止点，用vector容器装可以确保当鼠标移动时，直线也随之移动
//    std::vector<QPoint> m_endPoints;
    QPoint m_endPoint;
    //直线的画笔
    QPen m_pen;
};

//涂鸦
class Doodle
{
public:
    Doodle()    {    }
    Doodle(const QPen &pen)
        : m_pen(pen)    {    }
    Doodle(const Doodle &e)
    {        m_lines = e.m_lines;
             m_pen = e.m_pen;
    }
    Doodle & operator=(const Doodle &e)
    {
        if(this != &e)
        {
            m_lines = e.m_lines;
            m_pen = e.m_pen;
        }
        return *this;
    }
    ~Doodle()    {}
    QVector<QLineF> m_lines;
    QPen m_pen;
};

//裁剪
class CutRectElement
{
public:
    CutRectElement()   {    }
    CutRectElement(const QRectF &rect)
        :m_cutRect(rect)    {    }

    ~CutRectElement() {   }

    QRectF m_cutRect;
};

#endif // ELEMENTGROUP_H
