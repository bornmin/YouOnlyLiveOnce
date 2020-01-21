#include "RegisterCommonapi.h"

using namespace v1::commonapi;

RegisterCommonapi::RegisterCommonapi()
{

}

void RegisterCommonapi::run()
{
    std::cout <<"RegisterCommonapi thread start" <<std::endl;
    init();
}

void RegisterCommonapi::init()
{
    std::cout << __FUNCTION__<<std::endl;

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();    

    myProxy = runtime->buildProxy<HelloWorldProxy>("local", "shin");

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    std::string returnMessage;


    myProxy->getEnumBroadCastMethodEvent().subscribe([&](HelloWorld::testEnum value){
        std::cout << "Client Log!!  getEnumBroadCastMethodEvent value: " << value << std::endl;
        //QTTESTENUM testEnum = static_cast<QTTESTENUM>(value);
        int tmp = static_cast<int>(value);//enum값을 qt에서 사용할 enum값으로 변형하기위해서 int형으로 우선 변환해 줍니다.
        ConnectEvent::QTTESTENUM testEnum1 = static_cast<ConnectEvent::QTTESTENUM>(tmp);//변환된 int형 변수를 qt에서 사용할 enum값으로 변환해 줍니다.
        ConnectEvent::getInstance().openPopup(testEnum1);//qml의 팝업 출력하는 signal을 호출하는 connectEvent클래스의 함수를 호출해 줍니다.
        //이 함수로 발생시킨 signal로 qml의함수가 호출되고 qml의 함수는 팝업이 열려있으면 팝업을 닫아주고 팝업이 닫혀있으면 팝업을 출력해 줍니다.
    });
}
