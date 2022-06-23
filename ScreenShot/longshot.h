/*author:longxinping 2020051615040
 存在的问题：暂时只能在滚动条所在的窗口输入文本，进行截取长图。
 输入文本后按OK按钮进行截取图片。
 后续继续改进*/

#ifndef LONGSHOT_H
#define LONGSHOT_H

#include<QPushButton>
#include <QWidget>
#include<QScrollArea>
#include"ui_form.h"

class LongShot:public QWidget
{
    Q_OBJECT
public:
    LongShot(QWidget *parent=0);
    ~LongShot();
public slots:
    void longShot();
private:
    Ui::Form *ui;

};
#endif // LONGSHOT_H
