#include"RecScreen.h"
#include<QApplication>
#include<QDesktopServices>
#include<QScreen>
#include<QPixmap>
#include<QLabel>

//矩形选中框的宽度
#define SELECT_RECT_BORDER_WIDTH 1

//选中框变现上的小矩形和宽度和高度
#define STRETCH_RECT_WIDTH 6
#define STRETCH_RECT_HEIGHT 6

RectScreen::RectScreen(QWidget *parent) :QWidget(parent),m_currentCaptureState(InitCapture),m_isMousePressed(false){

    initWindow();
    loadBackgroundPixmap();
    initStretchRect();

}


RectScreen::~RectScreen(){

}

void RectScreen::initWindow(){
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowActive|Qt::WindowFullScreen);
}

void RectScreen::loadBackgroundPixmap(){
    m_loadPixmap = QApplication::primaryScreen()->grabWindow(0); //截取的是当前屏幕的照片

    //设置截取到的屏幕的宽和高
    m_screenWidth = m_loadPixmap.width();
    m_screenHeight = m_loadPixmap.height();
}

void RectScreen::setLabelInfo()
{
    QString labelInfo = QString("%1 * %2").arg(m_capturePixmap.width()).arg(m_capturePixmap.height());
    QFont sansFont("Helvetica[cronyx]",15);
    m_painter.setFont(sansFont);
    m_painter.setPen(QPen(Qt::white));
    m_painter.drawText(m_currentSelectRect.topLeft().x(),m_currentSelectRect.y() - 5,labelInfo);
}

void RectScreen::mousePressEvent(QMouseEvent *event){

    m_currentStretchState = getStretchRectState(event->pos());  //判断当前按下点是否处在伸缩区域。
    if(event->button() == Qt::LeftButton ){
        if(m_currentCaptureState == InitCapture){ //按下的是左键，并且现在的截屏状态是准备截屏前

            m_isMousePressed = true;
            m_currentCaptureState = BeginCaptureImage; //在”截屏前“这个状态按下按钮，表示开始截屏，状态切换，并且开始计算截取区域的开始点
            m_beginPoint = event->pos();


    }else if(isPressPointInSelectRect(event->pos())){  //按下的点包含在选取的矩形内部，激活移动矩形，状态切换为移动选取区域
        m_currentCaptureState = BeginMoveCaptureArea;
       // setCursor(Qt::SizeAllCursor);
        m_beginMovePoint = event->pos();  //存储”始移动点“这个坐标

    }else if(m_currentStretchState != NotSelect){

        //此时的状态是鼠标按下的位置位于伸缩调整的小矩形上，要设置开始移动的坐标点和不同的鼠标样式
        m_currentCaptureState = BeginMoveStretchRect;
        //在不同的伸缩位置有不同的鼠标样式
        setStretchCursorStyle(m_currentStretchState);
        m_beginMovePoint = event->pos();
    }
    }

}



void RectScreen::mouseMoveEvent(QMouseEvent *event){

    if(m_currentCaptureState == BeginCaptureImage){
        m_endPoint = event->pos();
        update();   //move事件需要不断更新是以为鼠标在不断地移动，屏幕每次需要对鼠标的位置进行刷新更新
    }else if(m_currentCaptureState == BeginMoveCaptureArea){
        m_endMovePoint = event->pos();
        update();
    }else if(m_currentCaptureState == BeginMoveStretchRect){

        //鼠标在移动过程中，在没释放鼠标之前，鼠标的样式保持为按下鼠标时设置的样式
        m_endMovePoint = event->pos();
        update();
        return QWidget::mouseMoveEvent(event);
    }

    //两种情况下的鼠标移动应该具有不一样的鼠标样式，区域选取状态下（BeginCaptureImage）应该是箭头状，移动选取区域的（BeginMoveCaptureArea）状态下应该是SizeAllCursor
    StretchRectState stretchState = getStretchRectState(event->pos());
    if(stretchState != NotSelect){
        setStretchCursorStyle(stretchState);
    }
    else if(isPressPointInSelectRect(event->pos())){

        setCursor(Qt::SizeAllCursor);

    }else if(!isPressPointInSelectRect(event->pos()) && m_currentCaptureState != BeginMoveCaptureArea){

        setCursor(Qt::ArrowCursor);
    }

    return QWidget::mouseMoveEvent(event);
}

bool RectScreen::isPressPointInSelectRect(QPoint pressPoint){
    QRect selectRect = getRect(m_beginPoint,m_endPoint);
    if(selectRect.contains(pressPoint)){
        return true;
    }
    return false;
}

void RectScreen::mouseReleaseEvent(QMouseEvent *event){

    //鼠标释放时鼠标的样式还是保持之前的样式不改变，所以不设置样式
    if(m_currentCaptureState == BeginCaptureImage){

        m_currentCaptureState = FinishCaptureImage;
        //m_currentCaptureState = InitCapture;
        m_endPoint = event->pos();
        update();

    }else if(m_currentCaptureState == BeginMoveCaptureArea){
        m_currentCaptureState = FinishMoveCaptureArea;
        m_endMovePoint = event->pos();
        update();
    }else if(m_currentCaptureState == BeginMoveStretchRect){
        m_currentCaptureState = FinishMoveStretchRect;
        m_endMovePoint = event->pos();
        update();
    }
   // m_isMousePressed = false;
}

void RectScreen::paintEvent(QPaintEvent *event){  //一旦鼠标进行移动，调用了update（），就会调用paintEvent（）处理绘画事件

    Q_UNUSED(event);
    m_painter.begin(this);
    QColor shadowColor(0,0,0,100);  //这里是为截屏时，没有选取的区域设置的阴影颜色，不可见度很高
    m_painter.setPen(QPen(Qt::blue,2,Qt::SolidLine,Qt::FlatCap));
    m_painter.drawPixmap(0,0,m_loadPixmap);//将抓取到的像素图进行绘制
    m_painter.fillRect(m_loadPixmap.rect(),shadowColor);//对没有抓取的区域进行阴影填充

    //这个区域被单独提取作为drawSelectImage（）函数
//    if(m_isMousePressed){//如果此时鼠标是按下的，证明还在继续选取要截屏的区域

//        QRect selectRect(m_beginPoint,m_endPoint);//设置现在选取矩形那个区域的位置和大小
//        m_capturePixmap = m_loadPixmap.copy(selectRect);//？？
//        m_painter.drawPixmap(selectRect.topLeft(),m_capturePixmap);//将这个捕捉到的像素图画从矩形框的左上角开始绘画
//        m_painter.drawRect(selectRect); //绘制由屏幕鼠标形成的矩形框

//    }
    switch (m_currentCaptureState) {
    case InitCapture:
        break;
    case BeginCaptureImage:
    case FinishCaptureImage:
    case BeginMoveCaptureArea:
    case FinishMoveCaptureArea:
    case BeginMoveStretchRect:
    case FinishMoveStretchRect:
        m_currentSelectRect = getSelectRect();
        drawCaptureImage();
    case FinishCapture:
        break;
    default:
        break;
    }
    setLabelInfo();
    m_painter.end();
}

void RectScreen::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape){
        close();
       // m_currentSelectRect = QRect(0,0,0,0);
        emit nullCapture();
    }
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        emit signalCompleteCapture(m_capturePixmap);
        close();

        //m_currentSelectRect = QRect(0,0,0,0);
    }
}



QRect RectScreen::getSelectRect(){

    QRect rect(0,0,0,0);
    if(m_currentCaptureState == BeginCaptureImage || m_currentCaptureState == FinishCaptureImage){

        //只是截取了屏幕，没有移动
       rect = getRect(m_beginPoint,m_endPoint);
    }

    if(m_currentCaptureState == BeginMoveCaptureArea || m_currentCaptureState == FinishMoveCaptureArea){

        //截取后对区域进行了移动
       rect = getMoveRect();
    }
    if(m_currentCaptureState == BeginMoveStretchRect || m_currentCaptureState == FinishMoveStretchRect){

        rect = getStretchRect();
    }
    if(m_currentCaptureState == FinishMoveCaptureArea || m_currentCaptureState == FinishCaptureImage || m_currentCaptureState == FinishMoveStretchRect){
        //所有的截图动作完成
        m_currentCaptureState = FinishCapture;
    }
    return rect;
}

QRect RectScreen::getRect(const QPoint &beginPoint,const QPoint &endPoint){

    int x,y,width,height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();
    //当选择的矩形的宽和高是0,则手动要设置宽和高最小为1
    QRect selectRect(x,y,width,height);
    if(selectRect.width() == 0){
        selectRect.setWidth(1);
    }
    if(selectRect.height() == 0){
        selectRect.setHeight(1);
    }
    return selectRect;
}

StretchRectState RectScreen::getStretchRectState(QPoint point)
{
    StretchRectState stretchState = NotSelect;
    if(m_topLeftRect.contains(point)){

       stretchState = TopLeftRect;

    }else if(m_topCenterRect.contains(point)){

            stretchState = TopCenterRect;

    }else if(m_topRightRect.contains(point)){

        stretchState = TopRightRect;

    }else if(m_rightCenterRect.contains(point)){

        stretchState = RightCenterRect;

    }else if(m_bottomRightRect.contains(point)){

        stretchState = BottomRightRect;

    }else if(m_bottomCenterRect.contains(point)){

        stretchState = BottomCenterRect;

    }else if(m_bottomLeftRect.contains(point)){

        stretchState = BottomLeftRect;

    }else if(m_leftCenterRect.contains(point)){
        stretchState = LeftCenterRect;
    }
    return stretchState;
}

void RectScreen::setStretchCursorStyle(StretchRectState states)
{
    switch(states){
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case TopLeftRect:
    case BottomRightRect:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRightRect:
    case BottomLeftRect:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case TopCenterRect:
    case BottomCenterRect:
        setCursor(Qt::SizeVerCursor);
        break;
    case LeftCenterRect:
    case RightCenterRect:
        setCursor(Qt::SizeHorCursor);
        break;
    default:break;

    }
}

void RectScreen::initStretchRect()
{
    m_currentStretchState = NotSelect;

    m_topLeftRect = QRect(0,0,0,0);
    m_topCenterRect = QRect(0,0,0,0);
    m_topRightRect = QRect(0,0,0,0);

    m_rightCenterRect = QRect(0,0,0,0);
    m_bottomRightRect = QRect(0,0,0,0);

    m_bottomCenterRect = QRect(0,0,0,0);
    m_bottomLeftRect = QRect(0,0,0,0);

    m_leftCenterRect = QRect(0,0,0,0);
}

//获得移动后的点
QRect RectScreen :: getMoveRect(){
    QPoint movePoint  = getMovePoint();

    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint  = m_endPoint + movePoint;

    if(m_currentCaptureState == FinishMoveCaptureArea){
        m_beginPoint = beginPoint;
        m_endPoint = endPoint;
        //将移动的点重新清零，不影响下次移动
        m_beginMovePoint = QPoint(0,0);
        m_endMovePoint = QPoint(0,0);
    }
    return QRect(beginPoint,endPoint);
}

//为了检查移动的点是否超出了电脑屏幕边界
QPoint RectScreen::getMovePoint(){

    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint,m_endPoint);

    //移动选取是否超出屏幕左边界
    if(currentRect.topLeft().x() + movePoint.x() < 0){
        movePoint.setX(0-currentRect.topLeft().x());
    }
    //移动选取是否超出屏幕上边界
    if(currentRect.topLeft().y() + movePoint.y() < 0){
        movePoint.setY(0 - currentRect.topLeft().y());
    }
    //移动选区是否超出屏幕右边界
    if(currentRect.bottomRight().x() + movePoint.x() > m_screenWidth){
        movePoint.setX(m_screenWidth - currentRect.bottomRight().x());
    }
    //移动选区是否超出下边界
    if(currentRect.bottomRight().y() + movePoint.y() > m_screenHeight){
        movePoint.setY(m_screenHeight - currentRect.bottomRight().y());
    }

    return movePoint;
}

QRect RectScreen::getStretchRect()
{
    QRect stretchRect;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    switch (m_currentStretchState)
    {
    case NotSelect:
        stretchRect = getRect(m_beginPoint, m_endPoint);
        break;
    case TopLeftRect:
    {
        stretchRect = getRect(currentRect.bottomRight(), m_endMovePoint);
    }
        break;
    case TopRightRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(beginPoint, endPoint);
    }
        break;
    case BottomLeftRect:
    {
        QPoint beginPoint = QPoint(m_endMovePoint.x() , currentRect.topLeft().y());
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, endPoint);
    }
        break;
    case BottomRightRect:
    {
        stretchRect = getRect(currentRect.topLeft(), m_endMovePoint);
    }
        break;
    case LeftCenterRect:
    {
        QPoint beginPoint = QPoint(m_endMovePoint.x(), currentRect.topLeft().y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case TopCenterRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case RightCenterRect:
    {
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    case BottomCenterRect:
    {
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    default:
    {
        stretchRect = getRect(m_beginPoint , m_endPoint );
    }
        break;
    }

    // 拖动结束更新 m_beginPoint , m_endPoint;
    if (m_currentCaptureState == FinishMoveStretchRect)
    {
        m_beginPoint = stretchRect.topLeft();
        m_endPoint = stretchRect.bottomRight();
    }

    return stretchRect;

}
void RectScreen::drawCaptureImage(){
    m_capturePixmap = m_loadPixmap.copy(m_currentSelectRect);
    m_painter.drawPixmap(m_currentSelectRect.topLeft(),m_capturePixmap);
    m_painter.drawRect(m_currentSelectRect);
    drawStretchRect();
}

void RectScreen::drawStretchRect()
{
    QColor color = QColor(0, 174, 255);
    // 四个角坐标;
    QPoint topLeft = m_currentSelectRect.topLeft();
    QPoint topRight = m_currentSelectRect.topRight();
    QPoint bottomLeft = m_currentSelectRect.bottomLeft();
    QPoint bottomRight = m_currentSelectRect.bottomRight();
    // 四条边中间点坐标;
    QPoint leftCenter = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect = QRect(topLeft.x() - STRETCH_RECT_WIDTH / 2, topLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topRightRect = QRect(topRight.x() - STRETCH_RECT_WIDTH / 2, topRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomLeftRect = QRect(bottomLeft.x() - STRETCH_RECT_WIDTH / 2, bottomLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomRightRect = QRect(bottomRight.x() - STRETCH_RECT_WIDTH / 2, bottomRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_leftCenterRect = QRect(leftCenter.x() - STRETCH_RECT_WIDTH / 2, leftCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topCenterRect = QRect(topCenter.x() - STRETCH_RECT_WIDTH / 2, topCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightCenterRect = QRect(rightCenter.x() - STRETCH_RECT_WIDTH / 2, rightCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomCenterRect = QRect(bottomCenter.x() - STRETCH_RECT_WIDTH / 2, bottomCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_painter.fillRect(m_topLeftRect, color);
    m_painter.fillRect(m_topRightRect, color);
    m_painter.fillRect(m_bottomLeftRect, color);
    m_painter.fillRect(m_bottomRightRect, color);
    m_painter.fillRect(m_leftCenterRect, color);
    m_painter.fillRect(m_topCenterRect, color);
    m_painter.fillRect(m_rightCenterRect, color);
    m_painter.fillRect(m_bottomCenterRect, color);


}
