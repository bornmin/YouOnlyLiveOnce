#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
  
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldStubDefault.hpp>
  
class HelloWorldStubImpl: public v1::commonapi::HelloWorldStubDefault {
public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();
    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);

    virtual void intDataMethod(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _parameter, intDataMethodReply_t _reply);
    virtual void enumMethod(const std::shared_ptr<CommonAPI::ClientId> _client, v1::commonapi::HelloWorld::testEnum _testEnumParameter, enumMethodReply_t _reply);
    virtual void structInMethod(const std::shared_ptr<CommonAPI::ClientId> _client, v1::commonapi::HelloWorld::testStruct _structParameter, structInMethodReply_t _reply);
    virtual void structOutMethod(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _input, structOutMethodReply_t _reply);

};
 
#endif /* HELLOWORLDSTUBIMPL_H_ */
