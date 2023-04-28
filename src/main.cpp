#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Backend *backend = new Backend(&app);

    qmlRegisterSingletonInstance<Backend>("Calculator", 1, 0, "Backend", backend);

    const QUrl url("qrc:/qml/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
