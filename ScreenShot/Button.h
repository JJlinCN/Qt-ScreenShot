#ifndef BUTTON_H
#define BUTTON_H
#include<QPushButton>

class Button:public QPushButton
{
    Q_OBJECT
public:
    Button(QString name,QWidget *parent=0):QPushButton(name,parent){}
signals:
    void cutScreen();
};

#endif // BUTTON_H
