#include "longshot.h"
#include<QPixmap>
#include<QVBoxLayout>
#include<QTextEdit>
#include<QScreen>
#include<QLabel>

LongShot::LongShot(QWidget *parent):QWidget(parent),ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->scroll->setGeometry(10,10,300,300);
    ui->scroll->setWidgetResizable(false);
    ui->scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scroll->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setGeometry(0,0,700,1200);
    QVBoxLayout *layout=new QVBoxLayout(ui->scrollAreaWidgetContents);
//    QLabel *label=new QLabel();
//    label->setText("111");
//    QLabel *label2=new QLabel();
//    label2->setText("222");
//    layout->addWidget(label);
//    layout->addWidget(label2);
    QTextEdit *textEdit=new QTextEdit;
    layout->addWidget(textEdit);
    connect(ui->ok,&QPushButton::clicked,this,&LongShot::longShot);
     //
//      QString txt=textEdit->toPlainText();
//      qDebug()<<txt;
//    textEdit->textCursor().insertImage(QImage("/root/MyProject/2.jpg"));
   //

}

void LongShot::longShot()
{
    QPixmap pix(ui->scrollAreaWidgetContents->size());
    ui->scrollAreaWidgetContents->render(&pix);
    pix.save("/root/MyProject/1.jpg");
}

LongShot::~LongShot()
{
    delete ui;
}
