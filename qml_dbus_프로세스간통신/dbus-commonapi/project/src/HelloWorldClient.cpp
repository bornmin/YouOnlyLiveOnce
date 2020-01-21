#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include  <v1/commonapi/HelloWorldProxy.hpp>

using namespace v1::commonapi;


int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>("local", "shin");

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    std::string returnMessage;
    myProxy->sayHello("Bob", callStatus, returnMessage);
    std::cout << "Got message: '" << returnMessage << "'\n";

    std::int32_t intData = 3;
    std::int32_t outputData;
    myProxy->intDataMethod(intData,callStatus,outputData);//int형 데이터를 매개변수로 하는 함수 호출
    std::cout << "Client Log!! outputData :" << outputData << std::endl;

    HelloWorld::testEnum testenum = HelloWorld::testEnum::TEST_THIRD;
    std::cout << "testenum:" << testenum << std::endl;
    myProxy->enumMethod(testenum,callStatus,outputData);//enum 데이터를 매개변수로 하는 함수 호출
    std::cout << "Client Log!!  outputData :" << outputData << std::endl;


    HelloWorld::testStruct teststruct;
    teststruct.setId("input Data");
    teststruct.setCode(12341234);
    myProxy->structInMethod(teststruct,callStatus,outputData);//구조체 데이터를 매개변수로 하는 함수 호출
    std::cout << "Client Log!!  outputData: " << outputData << std::endl;


    HelloWorld::testStruct outStruct;
    std::int32_t test;
    myProxy->structOutMethod(test,callStatus,outStruct);//구조체 데이터를 리턴 받는 함수 호출
    std::cout << "Client Log!!  outputData id: " << outStruct.getId() << std::endl;
    std::cout << "Client Log!!  outputData code: " << outStruct.getCode() << std::endl;



    myProxy->getEnumBroadCastMethodEvent().subscribe([&](HelloWorld::testEnum value){
        std::cout << "Client Log!!  getEnumBroadCastMethodEvent value: " << value << std::endl;
    });

    while (true) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

    return 0;
}
