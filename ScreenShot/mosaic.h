#ifndef MOSAIC_H
#define MOSAIC_H
#include<QWidget>

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
    void setMosaicImage(QImage img);
signals:
    void sendMosaicImage(QImage img);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
private:
    QImage m_ImageStart;
    QImage m_ImageFinal;
    QPoint m_point;
    QPoint m_oldPoint;
};

#endif // MOSAIC_H
