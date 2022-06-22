#ifndef SHOT_H
#define SHOT_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Shot; }
QT_END_NAMESPACE

class Shot : public QMainWindow
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);
public:
    Shot(QWidget *parent = nullptr);   
    QPushButton *OK;
   // QPushButton *save;
    ~Shot();
public slots:
   void fullScreen();
private:
   QString time1;
};
#endif // SHOT_H
