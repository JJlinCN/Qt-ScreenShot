#include "edit.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTextDocument>

Text::Text(QWidget *parent)
    : QTextEdit(parent),ispressed{false},m_beginPoint{0,0}
{

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    setPalette(palette);
    //this->grabKeyboard();
    //初始化文字编辑板为透明,但是有一个边框
    setFrameShape(Box);
    setFrameShadow(Plain);
    setTextColor(Qt::black);
    resize(43,25);
    adjustSize();
    connect(this->document(),&QTextDocument::contentsChange,this,&Text::textAreaChanged);

}

Text::~Text()
{
}

void Text::mousePressEvent(QMouseEvent *event)
{
    ispressed = true;
    m_beginPoint = event->pos();
//    if(this->rect().topRight() == event->pos()){
//        setCursor(Qt::SizeFDiagCursor);
//    }
}

void Text::mouseMoveEvent(QMouseEvent *event)
{
    //计算组件移动到的坐标应该使用鼠标移动到的当前坐标，减去之前鼠标按下的坐标
    if(ispressed){
        /*QPoint point(event->globalPosition().x() - event->scenePosition().x(),event->globalPosition().y()-event->scenePosition().y());*/
         move(event->globalPosition().toPoint() - m_beginPoint);
    }

}

void Text::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    ispressed = false;
}

void Text::keyPressEvent(QKeyEvent *event)
{
    //回车按键事件需要两个键都要写，不然无法响应

    //如果是回车按键，则隐藏文字区的边框，标识编辑完成
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){

        this->setFrameShape(NoFrame);
         qDebug() << " Enter pressed";
         event->accept();  //事件不再继续传递
    }else{

        //如果回车按钮，就是继续编辑文字，重新显示文字边框
        setFrameShape(Box);
        setFrameShadow(Plain);
        return QTextEdit::keyPressEvent(event);

    }
}

void Text::textAreaChanged()
{
   this->document()->adjustSize();
    if(this->document()){
       int newWidth = this->document()->size().width()+5;
       int newHeight = this->document()->size().height() + 20;
       if(newWidth != this->width()){
           this->setFixedWidth(newWidth);
       }
       if(newHeight != this->height()){
           this->setFixedHeight(newHeight);
       }
    }

}
