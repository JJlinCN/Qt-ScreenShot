#include <QApplication>
#include <QQmlApplicationEngine>
#include "capture.h"
#include  <QQmlContext>
#include <QQmlImageProviderBase>
#include "imgprovider.h"
//#include"filter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Capture *capture = new Capture;
    QQmlApplicationEngine engine;
   // Filter *filter=new Filter;
    engine.rootContext()->setContextProperty("capture",capture);
//    engine.rootContext()->setContextProperty("fullshot",fullscreen);
//    engine.rootContext()->setContextProperty("button",fullscreen->OK);
   // engine.rootContext()->setContextProperty("filter",filter);
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
