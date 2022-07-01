//author:longxinping 2020051615040
//This is a program to set LongShot
//这相当于一个写日记，记录生活的长截图功能，把拍的图片放入窗口中，在图片下面的文本框中输入当时的感受，想表达的心情，然后按截图按钮截长图

#ifndef LONGSHOT_H
#define LONGSHOT_H

#include<QPushButton>
#include <QWidget>
#include<QScrollArea>
#include<QTextEdit>
#include<QLabel>
#include"ui_form.h"

class LongShot:public QWidget
{
    Q_OBJECT
public:
    LongShot(QWidget *parent=0);
    ~LongShot();
public slots:
    void open();
    void longShot();
private:
    Ui::Form *ui;
    QImage m_Image;
    QPixmap m_pixmap;
    QLabel *label;
    QVBoxLayout *layout;
    QString path;
    QTextEdit *textEdit;
};
#endif // LONGSHOT_H
