//author：pengyueting 2020051615252
#ifndef FREECAPTURE_H
#define FREECAPTURE_H

#include <QWidget>
#include <QPainter>

//enum CaptureState{
//    InitCapture = 0,//开始截图前（准备截图状态）
//    BeginCaptureImage, //开始截取图形
//    FinishCaptureImage,  //完成截取图形
//    BeginMoveCaptureArea, //开始移动截取好的区域
//    FinishMoveCaptureArea, //完成截取的区域移动
//    FinishCapture  //整个截取过程完成
//};

class FreeCapture : public QWidget
{
    Q_OBJECT
public:
    explicit FreeCapture(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void initWindow();
    void loadBackgroundPixmap();

private:
    QPixmap m_loadPixmap;//加载背景图片
    int m_screenwidth;
    int m_screenheight;
    bool m_isMousePress;  //是否鼠标左击
    QPolygon  m_pPoints;   //点集合
    QPainter  m_painter;
    QPainter  m_imagePaint;


signals:
    // 通知截图完毕，并将截取图片传递给调用类;
    void signalCompleteCapture(QPixmap captureImage);

};

#endif // FREECAPTURE_H
