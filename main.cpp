#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "AppWorkArea.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<AppWorkArea>("ZHWidget", 1, 0,"AppWorkArea");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
