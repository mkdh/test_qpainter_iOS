#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "AppWorkArea.h"
#include <graphicslist.h>
GraphicsList* graphicPath;

int main(int argc, char *argv[])
{
    graphicPath = new GraphicsList();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<AppWorkArea>("ZHWidget", 1, 0,"AppWorkArea");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
