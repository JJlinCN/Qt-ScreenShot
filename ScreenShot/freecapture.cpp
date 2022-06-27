//author：pengyueting 2020051615252
//增加了可移动不规则选框功能
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
    m_pInitPoints.clear();
    m_beginMovePoint = QPoint(0,0);
    m_endMovePoint = QPoint(0,0);
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
        //首次选取，以线性的方式让用户自己画线条，然后用for循环将途中记录的所有点用drawLine连接，不封闭，此后每次update都会重新调用paintEvent重绘一边当前点集m_pInitPoints内部的所有点并连接，当用户画完了之后会释放鼠标，此时改变状态，让painter知道用户不再绘画多边形线条，此时再用drawPolygon画多边形painter会连接尾部和首部那两个点为线以封口，成为多边形
    for (int j= 0;j<m_pInitPoints.size()-1;j++)
        m_painter.drawLine(m_pInitPoints.at(j), m_pInitPoints.at(j+1));  //根据多边形点集中相邻的两个点绘制多边形线条,
    if(m_currentCaptureState == FinishCaptureImageFree)
    m_painter.drawPolygon(m_pInitPoints,Qt::WindingFill);//使用多边形画会自动将尾部首部两个点和上，odd奇偶填充规则默认
    if(m_currentCaptureState == BeginMoveCaptureAreaFree || m_currentCaptureState == FinishCaptureFree){ //当前处于移动多边形状态 或者最终选取
        movePolygonCaculator(); //获取移动后的多边形点集并更新
        drawCurrentSelectPolygon(); //根据更新的多边形点集将移动后的多边形画出来
    }
    m_painter.end();
}

void FreeCapture::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(!m_isMouseRelease) //如果鼠标没有被释放，说明是第一次按压，可以初始化，如果是释放之后二次按压尝试重新绘图，则拒绝用户这样做，只允许进入移动多边形选框
    m_isMousePress = true; //更新鼠标状态
    if(isPressPointInSelectPolygon(event->pos())){
        m_currentCaptureState = BeginMoveCaptureAreaFree;
        setCursor(Qt::SizeAllCursor);
        m_beginMovePoint = event->pos();
    }
}

void FreeCapture::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isMousePress&&!m_isMouseRelease){
        QPoint point = event->pos();  //当鼠标按压后
        m_pInitPoints.push_back(point);   //将当前鼠标的坐标加入多边形点集
        m_pPoints.push_back(point); //顺带用初始点集初始化移动点集m_pPoint,防止后续出现内存访问错误
        update();                     //在paintevent中进行绘制 激活paintEvent进行重绘，更新当前框的位置
    }
    if(m_currentCaptureState == BeginMoveCaptureAreaFree){
        setCursor(Qt::SizeAllCursor);
        m_endMovePoint = event->pos();
        update();
    }else setCursor(Qt::ArrowCursor);
}

void FreeCapture::mouseReleaseEvent(QMouseEvent * event)
{
    if(!m_isMouseRelease){
        m_currentCaptureState = FinishCaptureImageFree;
        m_isMouseRelease = true;  //通知第一次按压结束
        update(); //多边形绘制完成
    }
    if(m_currentCaptureState == BeginMoveCaptureAreaFree){
        setCursor(Qt::ArrowCursor);
        m_currentCaptureState = FinishCaptureFree;//移动释放后将状态设置为完成最终选取
        m_endMovePoint = event->pos();
        update();
            //结束选取之后调整坐标，防止计算不如人意
            m_beginMovePoint = QPoint(0,0);
            m_endMovePoint = QPoint(0,0);
            for(int i=0;i<m_pInitPoints.size();i++){
                m_pInitPoints[i]=m_pPoints[i]; //调整初始坐标
        }
    }
}

void FreeCapture::cutFinalImage(){
    QPainterPath path;
    if(m_currentCaptureState == FinishCaptureImageFree)//如果是第一次选取还没移动，则用最初的点集初始化路径
    path.addPolygon(m_pInitPoints);
    if(m_currentCaptureState == FinishCaptureFree) //如果是移动了选取，则用移动点集m_pPoints初始化路径
    path.addPolygon(m_pPoints); //用多边形的点来设置路径 m_pPoints内部存储的是多边形移动之后的点集
    //设置填充路径
    //Qt::OddEvenFill:指定使用奇偶填充规则填充区域。根据这个规则，我们可以使用下面的方法来确定一个点是否在形状内部。从该点画一条水平线到形状外的一个位置，并计算交叉点的数量。如果交点的个数是奇数，那么点就在形状的内部。该模式为默认模式。
    //Qt::WindingFill:指定使用非零缠绕规则填充区域。 有了这个规则，我们使用以下方法确定一个点是否在形状内部。 绘制一条从该点到形状外部位置的水平线。 确定每个交点处的线的方向是向上还是向下。 通过对每个交叉点的方向求和来确定绕组数。 如果数字不为零，则该点在形状内。 这种填充模式在大多数情况下也可以被视为闭合形状的交集。相当于交集也填充
    path.setFillRule(Qt::WindingFill);
//    QRegion region(m_pPoints,Qt::WindingFill);
    QImage img(m_loadPixmap.width(),m_loadPixmap.height(),QImage::Format_ARGB32);//32bit ARGB模式 和背景图一样大小
    m_imagePaint.begin(&img); //开始绘制
    m_imagePaint.setClipping(true); //启用裁剪
    //启用剪辑，并使用剪辑操作将画家的剪辑路径设置为给定路径
    m_imagePaint.setClipPath(path);//设置裁剪区域
    m_imagePaint.drawPixmap(0,0,m_loadPixmap); //将背景图画上img画布中
    m_imagePaint.setClipping(false); //结束给定路径剪辑
    m_imagePaint.end();
    QPixmap shotPixmap = QPixmap::fromImage(img);//裁剪之后依然是多边形放在画布上，需要单独把多边形矩形拿出来
    //返回多边形的边界矩形，如果多边形为空，则返回QRect(0,0,0,0)。
    shotPixmap = shotPixmap.copy(m_pPoints.boundingRect());//在带有多边形的画布上用多边形点集的边界矩形进行深拷贝 把那一块区域扣出来this is important!!!
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
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        cutFinalImage();
        close();
    }
}

bool FreeCapture::isPressPointInSelectPolygon(QPoint mousePressPoint){
    if(m_isMouseRelease&&m_currentCaptureState == FinishCaptureImageFree){
        QRect selectPolygon = m_pInitPoints.boundingRect(); //如果第一次释放了并且完成了选取才需要去判断是否位于初始多边形框内
        if(selectPolygon.contains(mousePressPoint)){
            return true;
        }
    }
    if(m_isMouseRelease&&m_currentCaptureState == FinishCaptureFree){
        QRect selectPolygon = m_pPoints.boundingRect(); //如果是移动后判断选取，则用移动点集判断
        if(selectPolygon.contains(mousePressPoint)){
            return true;
        }
    }
        return false; //默认返回false
}

void FreeCapture::movePolygonCaculator(){
    QPoint moveDistancePoint = m_endMovePoint - m_beginMovePoint; //获取每次移动的点之间的距离
    //多边形不好加边界检验，先搁置
    for(int i=0;i<m_pInitPoints.size();i++){//根据初始点集和偏移量获取移动点集
        m_pPoints[i]=m_pInitPoints[i]+moveDistancePoint;
    }

}

void FreeCapture::drawCurrentSelectPolygon(){
//    QPainterPath path;
//    path.addPolygon(m_pPoints);
//    path.setFillRule(Qt::WindingFill);
//    QPixmap fillPixmap;//把移动后重新绘制的新多边形利用clip在复制背景上剪切一份区域像素集填充到新多边形上
//    fillPixmap = m_loadPixmap.copy(m_loadPixmap.rect());
//    QPainter clipFillPixmap;
//    clipFillPixmap.begin(&fillPixmap);
//    clipFillPixmap.setClipping(true);
//    clipFillPixmap.setClipPath(path);
//    clipFillPixmap.setClipping(false);//采用多边形路径裁剪获取更新后的多边形像素集
////    m_painter.drawPixmap(m_pPoints[0],fillPixmap);
    m_painter.drawPolygon(m_pPoints,Qt::WindingFill);//重新绘制新多边形框
}
