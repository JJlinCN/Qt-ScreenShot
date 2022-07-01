/*
 * author:huangyihonh
 * date:2022/6/28
*/
#ifndef SHARE_H
#define SHARE_H

#include <QWidget>

class Share : public QWidget{
    Q_OBJECT
public:
    Share(QWidget *parent = nullptr);
    //对于share这个版块的功能全部使用Q_INVOKABLE声明，在qml端的成员在集成这个功能时直接在按钮需要对这个功能相应的地方调用下列函数即可（在expose这个类给qml的情况下）
    Q_INVOKABLE void shareToQQ();
    Q_INVOKABLE void shareToWeXin();
    Q_INVOKABLE void sendByEmail();
    Q_INVOKABLE void startPrint();
private:
    QImage m_img;

};

#endif // SHARE_H
