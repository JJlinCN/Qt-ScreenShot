#ifndef MOSAIC_H
#define MOSAIC_H
#include<QWidget>
#include"ui_mosaic.h"

class Mosaic:public QWidget
{
    Q_OBJECT

protected:
void paintEvent(QMouseEvent *e);

public:
    explicit Mosaic(QWidget *parent = nullptr);
    ~Mosaic();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui_Form2 *ui;
    QImage m_Image;
    QPixmap m_pixmap;
    QPoint m_point;
    QPoint m_oldPoint;
};

#endif // MOSAIC_H
