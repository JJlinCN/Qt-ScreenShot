/*
author:longxinping
date:2022/6/29
*/
#include "gifwidget.h"
#include<QApplication>
#include<QScreen>
#include<QDesktopServices>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFileDialog>
#include<QMouseEvent>
#include<QDialog>
#include<QPainter>

//设置布局
GifWidget::GifWidget(QWidget *parent):QWidget(parent)
{
        setObjectName(tr("GifWidget"));
        resize(800, 600);
       // setSizeGripEnabled(true);

        QVBoxLayout *verticalLayout = new QVBoxLayout(this);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0,0,0,0);

        widgetMain = new QWidget(this);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetMain->sizePolicy().hasHeightForWidth());
        widgetMain->setSizePolicy(sizePolicy1);
        verticalLayout->addWidget(widgetMain);

        widgetBottom = new QWidget(this);
        widgetBottom->setMinimumSize(0, 45);
        widgetBottom->setMaximumSize(8000, 45);

        QHBoxLayout *layoutBottom = new QHBoxLayout(widgetBottom);
        layoutBottom->setSpacing(6);
        layoutBottom->setContentsMargins(9,9,-1,-1);

        QLabel *labFps = new QLabel(widgetBottom);
        layoutBottom->addWidget(labFps);

        txtFps = new QLineEdit(widgetBottom);
        txtFps->setMaximumSize(50, 12580);
        txtFps->setAlignment(Qt::AlignCenter);
        layoutBottom->addWidget(txtFps);

        QLabel *labWidth = new QLabel(widgetBottom);
        layoutBottom->addWidget(labWidth);

        txtWidth = new QLineEdit(widgetBottom);
        txtWidth->setEnabled(true);
        txtWidth->setMaximumSize(50, 12580);
        txtWidth->setAlignment(Qt::AlignCenter);
        layoutBottom->addWidget(txtWidth);

        QLabel *labHeight = new QLabel(widgetBottom);
        layoutBottom->addWidget(labHeight);

        txtHeight = new QLineEdit(widgetBottom);
        txtHeight->setMaximumSize(50, 12580);
        txtHeight->setAlignment(Qt::AlignCenter);
        layoutBottom->addWidget(txtHeight);

        labStatus = new QLabel(widgetBottom);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setHeightForWidth(labStatus->sizePolicy().hasHeightForWidth());
        sizePolicy2.setVerticalStretch(0);
        labStatus->setSizePolicy(sizePolicy2);
        layoutBottom->addWidget(labStatus);

        btnStart = new QPushButton(widgetBottom);
        QSizePolicy sizePolicy;
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);
        layoutBottom->addWidget(btnStart);
        verticalLayout->addWidget(widgetBottom);

        QPushButton *btnClose = new QPushButton(widgetBottom);
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);
        layoutBottom->addWidget(btnClose);
        verticalLayout->addWidget(widgetBottom);

        labFps->setText(tr("帧率"));
        labWidth->setText(tr("宽度"));
        labHeight->setText(tr("高度"));
        btnStart->setText(tr("开始"));
        btnClose->setText(tr("关闭"));

        connect(btnStart, SIGNAL(clicked()), this, SLOT(record()));
        connect(txtWidth, SIGNAL(editingFinished()), this, SLOT(resizeForm()));
        connect(txtHeight, SIGNAL(editingFinished()), this, SLOT(resizeForm()));
        connect(btnClose, SIGNAL(clicked()), this, SLOT(closeAll()));

        borderWidth = 1;
        bgColor = QColor("grey");

        fps = 10;
        txtFps->setText(QString::number(fps));
        gifWriter = 0;

        timer = new QTimer(this);
        timer->setInterval(1000);
        connect(timer, &QTimer::timeout, this, &GifWidget::saveImage);

        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        installEventFilter(this);


        txtWidth->setEnabled(true);
        txtHeight->setEnabled(true);

        labStatus->setObjectName("labStatus");
}

//保存录屏
void GifWidget::saveImage()
{
    if (!gifWriter) {
        return;
    }

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))//由于qt4没有RGBA8888,采用最接近RGBA8888的是ARGB32,颜色会有点偏差
    QPixmap pix = QPixmap::grabWindow(0, x() + rectGif.x(), y() + rectGif.y(), rectGif.width(), rectGif.height());
    QImage image = pix.toImage().convertToFormat(QImage::Format_ARGB32);
#else
    QScreen *screen = QApplication::primaryScreen();
    QPixmap pix = screen->grabWindow(0, x() + rectGif.x(), y() + rectGif.y(), rectGif.width(), rectGif.height());
    QImage image = pix.toImage().convertToFormat(QImage::Format_RGBA8888);
#endif

    gif.GifWriteFrame(gifWriter, image.bits(), rectGif.width(), rectGif.height(), fps);
    count++;
    labStatus->setText(QString("正在录制 第 %1 帧").arg(count));
}

//开始录屏
void GifWidget::record()
{
    if (btnStart->text() == "开始") {
        if (0 != gifWriter) {
            delete gifWriter;
            gifWriter = 0;
        }

        fileName = QFileDialog::getSaveFileName(this, "选择保存位置", qApp->applicationDirPath() + "/", "视频(*.mkv)");
        if (fileName.isEmpty()) {
            return;
        }

        int width = txtWidth->text().toInt();
        int height = txtHeight->text().toInt();
        fps = txtFps->text().toInt();

        gifWriter = new Gif::GifWriter;
        bool bOk = gif.GifBegin(gifWriter, fileName.toLocal8Bit().data(), width, height, fps);
        if (!bOk) {
            delete gifWriter;
            gifWriter = 0;
            return;
        }

        count = 0;
        labStatus->setText("开始录制...");
        btnStart->setText("停止");
        //延时启动
        timer->setInterval(1000 / fps);
        QTimer::singleShot(1000, timer, SLOT(start()));
        //saveImage();
    } else {
        timer->stop();
        gif.GifEnd(gifWriter);

        delete gifWriter;
        gifWriter = 0;

        labStatus->setText(QString("录制完成 共 %1 帧").arg(count));
        btnStart->setText("开始");
        QDesktopServices::openUrl(QUrl(fileName));
    }
}

//设置窗口状态
void GifWidget::paintEvent(QPaintEvent *)
{
    int width = txtWidth->text().toInt();
    int height = txtHeight->text().toInt();

    rectGif = QRect(borderWidth,1, width-(borderWidth*2), height);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRoundedRect(this->rect(), 5, 5);
    //定义数字图像合成支持的模式。组合模式用于指定如何将源图像中的像素与目标图像中的像素合并。
    painter.setCompositionMode(QPainter::CompositionMode_Clear);//目标中的像素被清除(设置为完全透明)，独立于源。
    painter.fillRect(rectGif, Qt::SolidPattern);
}

//关闭录制屏幕面板
void GifWidget::closeAll()
{
    close();
    emit finish();
}

void GifWidget::resizeForm()
{
    int width = txtWidth->text().toInt();
    int height = txtHeight->text().toInt();
    resize(width, height+widgetBottom->height());
}

//判断鼠标/键盘的动作
bool GifWidget::eventFilter(QObject *watched, QEvent *e)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
    if(mouseEvent->type() == QEvent::MouseButtonPress)
    {
        if(mouseEvent->button() == Qt::LeftButton)
        {
            mousePressed = true;
            mousePoint = mouseEvent->globalPosition().toPoint() - this->pos();
            return true;
        }
    }
    else if(mouseEvent->type() == QEvent::MouseButtonRelease)
    {
        mousePressed = false;
        return true;
    }
    else if(mouseEvent->type() == QEvent::MouseMove)
    {
        if(mousePressed)
        {
            this->move(mouseEvent->globalPosition().toPoint() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(watched, e);
}

//改变指针位置
void GifWidget::resizeEvent(QResizeEvent *)
{
    txtWidth->setText(QString::number(widgetMain->width()));
    txtHeight->setText(QString::number(widgetMain->height()));
   // QDialog::resizeEvent(e);
}

GifWidget::~GifWidget()
{
    delete widgetMain;  widgetMain=nullptr;
    delete widgetBottom; widgetBottom=nullptr;
    delete txtFps;    txtFps=nullptr;
    delete txtWidth; txtWidth=nullptr;
    delete txtHeight; txtHeight=nullptr;
    delete gifWriter; gifWriter=nullptr;
    delete btnStart; btnStart=nullptr;
    delete closeButton; closeButton=nullptr;
    delete labStatus; labStatus=nullptr;
    delete timer;  timer=nullptr;
}

