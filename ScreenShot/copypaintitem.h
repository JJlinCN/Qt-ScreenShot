/*
author:huangyihong pengyueting longxinping
date:2022/6/29
*/
#ifndef COPYPAINTITEM_H
#define COPYPAINTITEM_H

#include <QQuickPaintedItem>
#include <QImage>
#include <QPaintEvent>
#include "elementgroup.h"

class CopyPaintItem:public QQuickPaintedItem
{
public:
    CopyPaintItem(QQuickItem *parent=0);
    void save(QString filePath);
    void paint(QPainter *painter);
    void paintEvent(QEvent *event);

    void saveTextElement(QPainter *painter);
    void saveCircleElement(QPainter *painter);
    void saveRectElement(QPainter *painter);
    void saveLineElement(QPainter* painter);
    void saveDoodleElement(QPainter *painter);
    void saveCutImg();
    QPainter *copyPainter;
    QVector<TextElement*> m_textElements;
    QVector<CircleElement*> m_circleElements;
    QVector<RectElement*> m_rectElements;
    QVector<LineElement*> m_lineElements;
    QVector<Doodle*> m_doodleElements;
    QVector<CutRectElement*> m_rects;
    QImage m_image;
};

#endif // COPYPAINTITEM_H
