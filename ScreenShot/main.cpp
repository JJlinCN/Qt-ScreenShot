#include <QApplication>
#include <QQmlApplicationEngine>
#include "capture.h"
#include <QQmlContext>
#include <QQmlImageProviderBase>
#include "imgprovider.h"
#include "filter.h"
#include "share.h" 
#include "longshot.h"
#include "gifwidget.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    //对于在软件中分享这个截图出去的功能，我已经把头文件包含，在qml中的使用方法请看“share.h”中的描述
    
    Capture *capture = new Capture;
    Share *share = new Share;
    LongShot *longshot = new LongShot;
    GifWidget *gifwidget = new GifWidget;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("capture",capture);
    engine.rootContext()->setContextProperty("share",share);
    engine.rootContext()->setContextProperty("gifwidget",gifwidget);
    engine.rootContext()->setContextProperty("longshot",longshot);
    engine.addImageProvider(QLatin1String("screen"),dynamic_cast<QQmlImageProviderBase *>(capture->imageProvider));
    const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
