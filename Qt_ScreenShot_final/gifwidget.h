//author:longxinping 2020051615040
//This is a program to record screen

#ifndef GIFWIDGET_H
#define GIFWIDGET_H

#include <QWidget>

#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QTimer>
#include"Gif.h"

class GifWidget:public QWidget
{
 Q_OBJECT
public:
    GifWidget(QWidget *parent=0);
    ~GifWidget();
signals:
    void finish();
public slots:
    void resizeForm();
    void saveImage();
    void record();
    void closeAll();
protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
private:
    QWidget *widgetMain;
    QWidget *widgetBottom;
    QLineEdit *txtFps;
    QLineEdit *txtWidth;
    QLineEdit *txtHeight;
    Gif gif;
    Gif::GifWriter *gifWriter;
    QPushButton *btnStart;
    QPushButton *closeButton;
    QLabel *labStatus;
    int borderWidth;
    int fps;
    int count;
    QColor bgColor;
    QRect rectGif;
    QString fileName;
    QTimer *timer;
};
#endif // GIFWIDGET_H
