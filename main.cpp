#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>

#include "modifimageprovider.h"
#include "paletteimageprovider.h"
#include "palettereceiver.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    const char *ui = "RECEIVER";
    qmlRegisterType<PaletteReceiver>(ui,1,0,"PaletteReceiver");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    PaletteReceiver firstStepButton;
    engine.rootContext()->setContextProperty("firstStepButton", &firstStepButton);
    engine.load(url);

    ModifImageProvider i_p;
    engine.addImageProvider("modification",&i_p);
    PaletteImageProvider i_p_p;
    engine.addImageProvider("palette",&i_p_p);

    QObject::connect(&i_p_p,SIGNAL(sendData(double *,int,int)),&i_p,SLOT(receiveDecomposition(double *,int,int)));
    QObject::connect(&firstStepButton,SIGNAL(xxChanged(QList<unsigned char>)),&i_p_p,SLOT(receivePalette(QList<unsigned char>)));
    QObject::connect(&firstStepButton,SIGNAL(xxChanged(QList<unsigned char>)),&i_p,SLOT(receivePalette(QList<unsigned char>)));




    return app.exec();
}
