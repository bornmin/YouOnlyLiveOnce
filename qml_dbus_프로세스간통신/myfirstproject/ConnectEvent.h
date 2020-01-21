#ifndef CONNECTEVENT_H
#define CONNECTEVENT_

#include <QQuickView>
#include <QObject>
#include <iostream>

using namespace std;
//struct TestStruct1{
//    QString title = "";
//    QString ButtonText = "";
//    QString Infomation = "";
//};
class ConnectEvent : public QObject//connection을 사용하기 위해 상속 받아야 하는 클래스
{

public:
    Q_OBJECT
    Q_ENUMS(WEEK)
    Q_ENUMS(QTTESTENUM)

public:// enum 클래스를 사용하기 위해 등록
#include <AllEnum.hpp>//enum값 들을 등록하기 위한 헤더파일
public:
    ConnectEvent();
    ~ConnectEvent();

    void init();

    static ConnectEvent &getInstance(); //singleton instance를 만들기 위한 함수

    void setWindow(QQuickWindow* Window);
    QQuickWindow *getWindow();

//    void setTestList();
//    Q_INVOKABLE int getListSize();
//    Q_INVOKABLE QString getListTitle(int index);
//    Q_INVOKABLE QString getListButtonText(int index);
//    Q_INVOKABLE QString getListInfomation(int index);
//    Q_INVOKABLE void deleteListItem(int index);

//    Q_INVOKABLE void cppCalledQmlFunction();

    void openPopup(QTTESTENUM value);

private:
    int value = 0;
    QQuickWindow* mMainView;
    //vector<TestStruct1> mTestList;
    QObject *mRootObject = nullptr;

signals:
    void cppSignalCommonapiBroadCastEvent(QVariant);
};

Q_DECLARE_METATYPE(ConnectEvent::WEEK)
Q_DECLARE_METATYPE(ConnectEvent::QTTESTENUM)

#endif // CONNECTEVENT_H
