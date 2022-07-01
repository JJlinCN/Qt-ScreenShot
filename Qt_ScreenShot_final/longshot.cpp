/*
author:longxinping
date:2022/6/29
*/
#include "longshot.h"
#include<QPixmap>
#include<QVBoxLayout>
#include<QTextEdit>
#include<QFileDialog>
#include<QTextDocument>
#include<QScreen>
#include<QLabel>

//设置滑动栏
LongShot::LongShot(QWidget *parent):QWidget(parent),ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->scroll->setGeometry(10,10,200,200);
    ui->scroll->setWidgetResizable(false);
    ui->scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scroll->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setGeometry(0,0,600,700);
    layout=new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setMaximumHeight(500);

    connect(ui->openImage,&QPushButton::clicked,this,&LongShot::open);
    connect(ui->ok,&QPushButton::clicked,this,&LongShot::longShot);
    textEdit=new QTextEdit;
    label=new QLabel;
}

//保存截图图片
void LongShot::longShot()
{
    QPixmap pix(ui->scrollAreaWidgetContents->size());
    ui->scrollAreaWidgetContents->render(&pix);
    QString path=QFileDialog::getSaveFileName(this,tr("另存为"),tr(""),tr("图片(*.png *.jpeg *.jpg)"));
    pix.save(path);
}
//打开文件，添加要加入的图片
void LongShot::open()
{
    path=QFileDialog::getOpenFileName();
    m_Image.load(path);
    m_pixmap = QPixmap::fromImage(m_Image).scaled(size()/*,Qt::KeepAspectRatio,Qt::SmoothTransformation*/);
    label->setPixmap(m_pixmap);
    label->setScaledContents(true);
    layout->addWidget(label);
    layout->addWidget(textEdit);
    update();
}

LongShot::~LongShot()
{
    delete ui;
    delete label;
    delete textEdit;
    delete layout;
    label=nullptr;
    textEdit=nullptr;
    layout=nullptr;
}
