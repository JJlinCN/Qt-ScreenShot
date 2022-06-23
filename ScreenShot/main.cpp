#include <QApplication>
#include <QQmlApplicationEngine>
#include "capture.h"
#include "shot.h"
#include  <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Capture *capture = new Capture;
    Shot *fullscreen = new Shot();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("capture",capture);
    engine.rootContext()->setContextProperty("fullshot",fullscreen);
    engine.rootContext()->setContextProperty("button",fullscreen->OK);
    const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
