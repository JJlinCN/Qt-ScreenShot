//author：pengyueting 2020051615252
#ifndef FREECAPTURE_H
#define FREECAPTURE_H

#include <QWidget>
#include <QPainter>

enum CaptureStateFree{
    InitCaptureFree = 0,//开始选取前（准备截图状态）
    FinishCaptureImageFree,  //完成选取图形
    BeginMoveCaptureAreaFree, //开始移动选取好的区域
    FinishMoveCaptureAreaFree, //完成选取的区域移动
    FinishCaptureFree  //整个截取过程完成
};

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
    void cutFinalImage();
private:
    void initWindow();
    void loadBackgroundPixmap();

private:
    CaptureStateFree m_currentCaptureState;
    QPixmap m_loadPixmap;//加载背景图片
    QPixmap m_capturePixmap; //捕捉到的像素集
    int m_screenwidth;
    int m_screenheight;
    bool m_isMousePress;  //是否鼠标左击
    bool m_isMouseRelease;//是否鼠标二次点击
    QPolygon  m_pPoints;   //点集合
    QPainter  m_painter;
    QPainter  m_imagePaint;
    QRect m_currentSelectRect;
signals:
    // 通知截图完毕，并将截取图片传递给调用类;
    void signalCompleteCapture(QPixmap captureImage);

};

#endif // FREECAPTURE_H
