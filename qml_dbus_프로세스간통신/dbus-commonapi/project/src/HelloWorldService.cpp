#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "HelloWorldStubImpl.hpp"
#include <unistd.h>
  
using namespace std;


  
int main() {

    int i = 0;
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();    
    std::shared_ptr<HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
    if(runtime->registerService("local", "shin", myService)){
         std::cout << "Service registered." << std::endl;
    }else{
        std::cout << "Service not registered." << std::endl;
    }
    std::cout << "Successfully Registered Service!" << std::endl;

    std::thread broadcastMethod([&]() {
          bool loop = true;
          while(loop){

              if (true == loop) {
                  std::cout <<"send broad cast method" << std::endl;
                   myService->fireEnumBroadCastMethodEvent(v1::commonapi::HelloWorld::testEnum::TEST_THIRD);
                  sleep(3); // 3s
              }
          }
      });
      broadcastMethod.detach();
 
    while (true) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));

    }
  
    return 0;
 } 
