#include "ConnectEvent.h"


ConnectEvent::ConnectEvent()
{    
    cout << "ConnectEvent" << endl;
    //setTestList();//생성자에서 호출해서 객체가 만들어 지자마자 데이터를 vector에 담는다.
    qmlRegisterType<ConnectEvent>("ConnectEvent", 1, 0, "ConnectEvent");//class를 qml에서 사용하기 위해서 등록해주는 부분
}

ConnectEvent::~ConnectEvent()
{
}

void ConnectEvent::init()
{
    std::cout <<__FUNCTION__<<std::endl;
    QObject::connect(this,SIGNAL(cppSignalCommonapiBroadCastEvent(QVariant)),mMainView,SLOT(qmlSlotCommonapiBroadCastEvent(QVariant)));
}

ConnectEvent &ConnectEvent::getInstance()
{
    static ConnectEvent *mpInstance;
    if(mpInstance == nullptr){
        mpInstance = new ConnectEvent();
    }
    return *mpInstance;
}

void ConnectEvent::setWindow(QQuickWindow* Window)
{
    std::cout << "setWindow called "<<std::endl;
    mMainView = Window;//connection을 해주기 위해 윈도우를 등록       
}

QQuickWindow *ConnectEvent::getWindow()
{
    std::cout << "getWindow called "<<std::endl;    
    return mMainView;
}

//void ConnectEvent::setTestList()
//{
//    std::cout << "setTestList called "<<std::endl;
//    TestStruct1 testStruct;
//    testStruct.title = "Sunday is enum = 0";
//    testStruct.ButtonText = "Sunday" ;
//    testStruct.Infomation = "Sunday is hollyday";
//    mTestList.push_back(testStruct);

//    testStruct.title = "Monday is enum = 1";
//    testStruct.ButtonText = "Monday" ;
//    testStruct.Infomation = "Monday is Work day";
//    mTestList.push_back(testStruct);

//    testStruct.title = "Tuesday is enum = 2";
//    testStruct.ButtonText = "Tuesday" ;
//    testStruct.Infomation = "Tuesday is Work day";
//    mTestList.push_back(testStruct);

//    testStruct.title = "wednesday is enum = 3";
//    testStruct.ButtonText = "wednesday" ;
//    testStruct.Infomation = "wednesday is Work day";
//    mTestList.push_back(testStruct);

//    testStruct.title = "Thursday is enum = 4";
//    testStruct.ButtonText = "Thursday" ;
//    testStruct.Infomation = "Thursday is Work day";
//    mTestList.push_back(testStruct);

//    testStruct.title = "Friday is enum = 5";
//    testStruct.ButtonText = "Friday" ;
//    testStruct.Infomation = "Friday is Work day";
//    mTestList.push_back(testStruct);

//    testStruct.title = "Saturday is enum = 6";
//    testStruct.ButtonText = "Saturday" ;
//    testStruct.Infomation = "Saturday is hollyday";
//    mTestList.push_back(testStruct);

//    testStruct.title = "test data 7";
//    testStruct.ButtonText = "test data 7" ;
//    testStruct.Infomation = "test data 7";
//    mTestList.push_back(testStruct);

//    testStruct.title = "test data 8";
//    testStruct.ButtonText = "test data 8" ;
//    testStruct.Infomation = "test data 8";
//    mTestList.push_back(testStruct);
//}

//int ConnectEvent::getListSize()//리스트의 크기를 가져오기 위함 함수
//{
//    return mTestList.size();
//}

//QString ConnectEvent::getListTitle(int index)//리스트 인덱스의 제목을 가져오기 위한 함수
//{
//    return mTestList.at(index).title;
//}

//QString ConnectEvent::getListButtonText(int index)//리스트 인덱스의 버튼 텍스트를 가져오기 위한 함수
//{
//    return mTestList.at(index).ButtonText;
//}

//QString ConnectEvent::getListInfomation(int index)//리스트 인덱스의 내부 정보를 가져오기 위한 함수
//{
//    return mTestList.at(index).Infomation;
//}

//void ConnectEvent::deleteListItem(int index)//c++ 리스트의 데이터를 삭제
//{
//    int count = 0;
//    std::cout << "deleteListItem index:" << index << std::endl;
//    std::cout << "deleteListItem ListInfomation:" << getListInfomation(index).toStdString() << std::endl;
//    for(std::vector<TestStruct1>::iterator it = mTestList.begin(); it != mTestList.end(); it++){
//        if(count == index){
//            std::cout << "delete count:" << count<<std::endl;
//            it = mTestList.erase(it);
//            break;
//        }else{
//            count++;
//        }
//    }
//     std::cout << "mTestList.size:" << mTestList.size()<<std::endl;

//}

//void ConnectEvent::cppCalledQmlFunction(){

//    std::cout << "cppCalledQmlFunction called :"<<std::endl;
//    if(mRootObject == nullptr)
//        mRootObject = qobject_cast<QObject *>(getInstance().getWindow());
//    QMetaObject::invokeMethod(mRootObject, "qmlSlotFromCpp", Q_ARG(QVariant, "String 매개변수 테스트"),Q_ARG(QVariant, 100));//qml 함수를 호출하는데 string 형 매개변수와 int형 매개변수를 넣어서 호출해주는 부분
//}

void ConnectEvent::openPopup(ConnectEvent::QTTESTENUM value)
{
    std::cout << __FUNCTION__<<std::endl;
    emit cppSignalCommonapiBroadCastEvent(value);
}





