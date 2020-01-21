#include "HelloWorldStubImpl.hpp"
 
HelloWorldStubImpl::HelloWorldStubImpl() { }
HelloWorldStubImpl::~HelloWorldStubImpl() { }
  
void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _reply) {
    std::stringstream messageStream;
    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";
 
    _reply(messageStream.str());
}

void HelloWorldStubImpl::intDataMethod(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _parameter, v1::commonapi::HelloWorldStub::intDataMethodReply_t _reply)
{
    std::cout << __FUNCTION__<<" server log parameter: " << _parameter << std::endl;
    std::int32_t returnData = 100;
    _reply(returnData);
}

void HelloWorldStubImpl::enumMethod(const std::shared_ptr<CommonAPI::ClientId> _client, v1::commonapi::HelloWorld::testEnum _testEnumParameter, v1::commonapi::HelloWorldStub::enumMethodReply_t _reply)
{
    std::cout << __FUNCTION__<<" server log _testEnumParameter: " << _testEnumParameter << std::endl;
    std::int32_t returnData = 101;
    _reply(returnData);
}

void HelloWorldStubImpl::structInMethod(const std::shared_ptr<CommonAPI::ClientId> _client, v1::commonapi::HelloWorld::testStruct _structParameter, v1::commonapi::HelloWorldStub::structInMethodReply_t _reply)
{
    std::cout << __FUNCTION__<<" server log _structParameter id: " << _structParameter.getId() << std::endl;
    std::cout << __FUNCTION__<<" server log _structParameter code: " << _structParameter.getCode() << std::endl;
    std::int32_t returnData = 102;
    _reply(returnData);
}

void HelloWorldStubImpl::structOutMethod(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _input, v1::commonapi::HelloWorldStub::structOutMethodReply_t _reply)
{
    std::cout << __FUNCTION__<<" server log _input: " << _input << std::endl;
    v1::commonapi::HelloWorld::testStruct returnStruct;
    returnStruct.setId("returnData");
    returnStruct.setCode(103);
    _reply(returnStruct);
}

