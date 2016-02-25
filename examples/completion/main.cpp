#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "emooj.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    com::cutehacks::emooj::registerEngine(&engine);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

