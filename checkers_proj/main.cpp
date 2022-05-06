#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mytablemodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //Иной способ регистрации: qt.io/blog/qml-type-registration-in-qt-5.15
    //Детальнее про регистрацию: https://doc.qt.io/qt-5/qtqml-cppintegration-overview.html
    qmlRegisterType<TableModel>("TableModel", 1, 0, "TableModel");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
