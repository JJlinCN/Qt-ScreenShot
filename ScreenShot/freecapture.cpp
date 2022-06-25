//author：pengyueting 2020051615252
//解决了多边形合并，但是无法判断当前鼠标坐标位于多边形内部,需要解决判断内部，多边形的移动和移动中展示
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QPainterPath>

#include "freecapture.h"

FreeCapture::FreeCapture(QWidget *parent) : QWidget(parent)
  ,m_currentCaptureState(InitCaptureFree),m_isMousePress(false),m_isMouseRelease(false)
{
    initWindow();
    loadBackgroundPixmap();
    m_pPoints.clear();//清除多边形点集
}

//初始化窗口
void FreeCapture::initWindow()
{
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
}

//获取当前屏幕
void FreeCapture::loadBackgroundPixmap()
{
    m_loadPixmap = QApplication::primaryScreen()->grabWindow(0); //抓取当前屏幕的图片;
    m_screenwidth = m_loadPixmap.width();
    m_screenheight = m_loadPixmap.height();
}

void FreeCapture::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    m_painter.begin(this);          //进行重绘;
    QColor shadowColor = QColor(0, 0, 0, 100);                      //阴影颜色设置;
    m_painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
    m_painter.drawPixmap(0, 0, m_loadPixmap);                       //将背景图片画到窗体上;
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);           //画影罩效果;
    m_painter.setRenderHint(QPainter::Antialiasing,true);           //路线优化，指示引擎应尽可能消除原语边缘的锯齿。抗锯齿
    if(m_currentCaptureState == InitCaptureFree)
        //首次选取，以线性的方式让用户自己画线条，然后用for循环将途中记录的所有点用drawLine连接，不封闭，此后每次update都会重新调用paintEvent重绘一边当前点集m_pPoints内部的所有点并连接，当用户画完了之后会释放鼠标，此时改变状态，让painter知道用户不再绘画多边形线条，此时再用drawPolygon画多边形painter会连接尾部和首部那两个点为线以封口，成为多边形
    for (int j= 0;j<m_pPoints.size()-1;j++)
        m_painter.drawLine(m_pPoints.at(j), m_pPoints.at(j+1));  //根据多边形点集中相邻的两个点绘制多边形线条,
    if(m_currentCaptureState == FinishCaptureImageFree)
    m_painter.drawPolygon(m_pPoints,Qt::WindingFill);//使用多边形画会自动将尾部首部两个点和上，odd奇偶填充规则默认
    m_painter.end();
}

void FreeCapture::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(!m_isMouseRelease) //如果鼠标没有被释放，说明是第一次按压，可以初始化，如果是释放之后二次按压尝试重新绘图，则拒绝用户这样做，只允许进入移动多边形选框
    m_isMousePress = true; //更新鼠标状态
}

void FreeCapture::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isMousePress&&!m_isMouseRelease){
        QPoint point = event->pos();  //当鼠标按压后
        m_pPoints.push_back(point);   //将当前鼠标的坐标加入多边形点集
        update();                     //在paintevent中进行绘制 激活paintEvent进行重绘，更新当前框的位置
    }
}

void FreeCapture::mouseReleaseEvent(QMouseEvent *)
{
    m_currentCaptureState = FinishCaptureImageFree;
    m_isMouseRelease = true;  //通知第一次按压结束
    update(); //多边形绘制完成
    //
}

void FreeCapture::cutFinalImage(){
    QPainterPath path;
    path.addPolygon(m_pPoints); //用多边形的点来设置路径
    //设置填充路径
    //Qt::OddEvenFill:指定使用奇偶填充规则填充区域。根据这个规则，我们可以使用下面的方法来确定一个点是否在形状内部。从该点画一条水平线到形状外的一个位置，并计算交叉点的数量。如果交点的个数是奇数，那么点就在形状的内部。该模式为默认模式。
    //Qt::WindingFill:指定使用非零缠绕规则填充区域。 有了这个规则，我们使用以下方法确定一个点是否在形状内部。 绘制一条从该点到形状外部位置的水平线。 确定每个交点处的线的方向是向上还是向下。 通过对每个交叉点的方向求和来确定绕组数。 如果数字不为零，则该点在形状内。 这种填充模式在大多数情况下也可以被视为闭合形状的交集。相当于交集也填充
    path.setFillRule(Qt::WindingFill);
    QImage img(m_loadPixmap.width(),m_loadPixmap.height(),QImage::Format_ARGB32);//32bit ARGB模式 和背景图一样大小

    m_imagePaint.begin(&img); //开始绘制
    m_imagePaint.setClipping(true); //启用裁剪
    //启用剪辑，并使用剪辑操作将画家的剪辑路径设置为给定路径
    m_imagePaint.setClipPath(path);//设置裁剪路径
    m_imagePaint.drawPixmap(0,0,m_loadPixmap); //将背景图画上
    m_imagePaint.setClipping(false); //结束给定路径剪辑
    m_imagePaint.end();

    QPixmap shotPixmap = QPixmap::fromImage(img);
    //返回多边形的边界矩形，如果多边形为空，则返回QRect(0,0,0,0)。
    shotPixmap = shotPixmap.copy(m_pPoints.boundingRect()); //深拷贝
    setVisible(false);


    //发送信号 将矩形截取的图片在界面显示
    emit signalCompleteCapture(shotPixmap);
}

void FreeCapture::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape){
        //退出截图
        close();
    }
//    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
//        emit signalCompleteCapture(m_capturePixmap);
//        close();

//        //m_currentSelectRect = QRect(0,0,0,0);
//    }
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        cutFinalImage();
        close();
    }
}
