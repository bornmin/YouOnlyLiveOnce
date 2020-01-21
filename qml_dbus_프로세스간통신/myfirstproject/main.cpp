#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <RegisterCommonapi.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;   

    ConnectEvent::getInstance(); //뷰가 그려지기 전에 객체를 생성해서 필요한 것들을 미리 만들어 준다.    

    RegisterCommonapi *registerCommonapi = new RegisterCommonapi();

    registerCommonapi->start();
    //RegisterCommonapi::getInstance().start();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *root = engine.rootObjects()[0];//qrc:/main.qml를 등록한 엔진의 object값을 가져옴

    ConnectEvent::getInstance().setWindow(qobject_cast<QQuickWindow *>(root));//qrc:/main.qml를 등록한 엔진의 object값을 window타입으로 변경해준다.
    ConnectEvent::getInstance().init();
    //event->cppCalledQmlFunction();
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
