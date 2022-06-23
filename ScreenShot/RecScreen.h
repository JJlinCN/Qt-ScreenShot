#ifndef RECSCREEN_H
#define RECSCREEN_H

#include<QtWidgets>
#include<QPainter>
class QLabel;

enum CaptureState{
    InitCapture = 0,//开始截图前（准备截图状态）
    BeginCaptureImage, //开始截取图形
    FinishCaptureImage,  //完成截取图形
    BeginMoveCaptureArea, //开始移动截取好的区域
    FinishMoveCaptureArea, //完成截取的区域移动
    BeginMoveStretchRect, //开始对截取的矩形做伸缩
    FinishMoveStretchRect, // 矩形伸缩完成
    FinishCapture  //整个截取过程完成
};

enum StretchRectState{
    NotSelect = 0,
    TopLeftRect,
    TopCenterRect,
    TopRightRect,
    RightCenterRect,
    BottomRightRect,
    BottomCenterRect,
    BottomLeftRect,
    LeftCenterRect
};

class RectScreen:public QWidget{

    Q_OBJECT

public:
    RectScreen(QWidget *parent = nullptr);
    ~RectScreen();
signals:
    void signalCompleteCapture(QPixmap captureImage);  //完成截图信号
    void nullCapture();
    //void finishSaveImage();
public slots:
  //  void cutScreen(QPixmap imagePixmap);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent*event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;  //当最后鼠标释放后，对不同的状态进行绘制选取框和选取图片

private:
    QRect getSelectRect(); //获取选取的矩形，有三种情况：只截取区域、截取后有移动、截取区域有伸缩

    QPoint getMovePoint();  //

    QRect getMoveRect();
    QRect getStretchRect();

    void drawCaptureImage();
    void drawStretchRect();
    void loadBackgroundPixmap();
    void setLabelInfo();

    void initWindow();

    bool isPressPointInSelectRect(QPoint pressPoint);

    QRect getRect(const QPoint &beginPoint,const QPoint &endPoint);

   void initStretchRect();//在才激活截屏这个功能时，八个小矩形初始化

   StretchRectState getStretchRectState(QPoint point);
   void setStretchCursorStyle(StretchRectState states);

private:
    CaptureState m_currentCaptureState;

   bool m_isMousePressed;  //用来判断事件发生时按键是否是按下的，鼠标的按键是否按下，有不同的处理方法

    QPixmap m_loadPixmap;  //要加载的像素集
    QPixmap m_capturePixmap; //捕捉到的像素集

    QPoint m_beginPoint; //没有涉及到移动的开始点和结束点坐标，用于计算选取的矩形的大小和位置
    QPoint m_endPoint;

    /*当每次选取时有鼠标进行移动时，就会计算点的开始移动时的坐标和点结束移动时的坐标。如果截屏的区域有移动的动作，最终选取区域的位置和大小需要
    m_beginPoint m_endPoint  m_beginMovePoint  m_endMovePoint同时来计算获取*/
    QPoint m_beginMovePoint;
    QPoint m_endMovePoint;

    QPainter m_painter; //画笔，绘制阴影区域和选取的矩形框和伸缩小矩形

    //伸缩边框上的八个小矩形
    QRect m_topLeftRect,m_topCenterRect,m_topRightRect,m_rightCenterRect,
           m_bottomRightRect,m_bottomCenterRect,m_bottomLeftRect,m_leftCenterRect;

    StretchRectState m_currentStretchState;

    QRect m_currentSelectRect;
    int m_screenWidth;
    int m_screenHeight;
    //int m_imageCount;
    //QLabel  *label;
};

#endif // RECSCREEN_H
