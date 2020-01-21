QT += quick quickcontrols2
CONFIG += c++11 dbus ## add shin dbus

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
_ROOT = $$_PRO_FILE_PWD_ #.pro .pro 파일이 있는 위치
INCLUDEPATH += $$_ROOT/src-gen #자신의 프로젝트에서 풀경로로 안해도 경로를 찾아 줄수 있도록 추가하는 부분
SOURCES += main.cpp \
    ConnectEvent.cpp \
    RegisterCommonapi.cpp \
    src-gen/v1/commonapi/HelloWorldDBusDeployment.cpp \
    src-gen/v1/commonapi/HelloWorldDBusProxy.cpp \
    src-gen/v1/commonapi/HelloWorldDBusStubAdapter.cpp \
    src-gen/v1/commonapi/HelloWorldStubDefault.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ConnectEvent.h \
    AllEnum.hpp \
    RegisterCommonapi.h \
    src-gen/v1/commonapi/HelloWorld.hpp \
    src-gen/v1/commonapi/HelloWorldDBusDeployment.hpp \
    src-gen/v1/commonapi/HelloWorldDBusProxy.hpp \
    src-gen/v1/commonapi/HelloWorldDBusStubAdapter.hpp \
    src-gen/v1/commonapi/HelloWorldProxy.hpp \
    src-gen/v1/commonapi/HelloWorldProxyBase.hpp \
    src-gen/v1/commonapi/HelloWorldStub.hpp \
    src-gen/v1/commonapi/HelloWorldStubDefault.hpp

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../dbus-commonapi/capicxx-core-runtime/build/release/ -lCommonAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../dbus-commonapi/capicxx-core-runtime/build/debug/ -lCommonAPI
else:unix: LIBS += -L$$PWD/../../dbus-commonapi/capicxx-core-runtime/build/ -lCommonAPI

INCLUDEPATH += $$PWD/../../dbus-commonapi/capicxx-core-runtime/include
DEPENDPATH += $$PWD/../../dbus-commonapi/capicxx-core-runtime/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../dbus-commonapi/capicxx-dbus-runtime/build/release/ -lCommonAPI-DBus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../dbus-commonapi/capicxx-dbus-runtime/build/debug/ -lCommonAPI-DBus
else:unix: LIBS += -L$$PWD/../../dbus-commonapi/capicxx-dbus-runtime/build/ -lCommonAPI-DBus

INCLUDEPATH += $$PWD/../../dbus-commonapi/capicxx-dbus-runtime/include
DEPENDPATH += $$PWD/../../dbus-commonapi/capicxx-dbus-runtime/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../dbus-commonapi/dbus-1.13.12/dbus/.libs/release/ -ldbus-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../dbus-commonapi/dbus-1.13.12/dbus/.libs/debug/ -ldbus-1
else:unix: LIBS += -L$$PWD/../../dbus-commonapi/dbus-1.13.12/dbus/.libs/ -ldbus-1

INCLUDEPATH += $$PWD/../../dbus-commonapi/dbus-1.13.12
DEPENDPATH += $$PWD/../../dbus-commonapi/dbus-1.13.12
