#ifndef FILTER_H
#define FILTER_H
#include"ui_filter.h"
#include"mosaic.h"
#include <QWidget>

class Filter : public QWidget
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = nullptr);
    ~Filter();

    void coolImage(int delta);
    void warmImage(int delta);

    Q_INVOKABLE void mosaic();

private slots:
    void on_open_clicked();

    void grey();
    void old();
    void warm();
    void cool();
    void vague();
    void reverse();
    void sharpen();
    void soften();

    void on_btn_saveas_clicked();

private:
    Ui::Form *ui;
    QImage m_Image;
    QPixmap m_pixmap;     //像素图
};
#endif // FILTER_H
