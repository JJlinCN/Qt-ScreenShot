#ifndef EDIT_H
#define EDIT_H
#include <QTextEdit>
#include <QPoint>


class Text : public QTextEdit{

    Q_OBJECT
//编辑中的文字编辑元素
public:
    Text(QWidget *parent = nullptr);
    ~Text();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
public slots:
    void textAreaChanged();

private:
    bool ispressed;
    QPoint m_beginPoint;
};
#endif // EDIT_H
