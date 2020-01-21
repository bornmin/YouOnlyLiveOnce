#ifndef REGISTERCOMMONAPI_H
#define REGISTERCOMMONAPI_H

#include <QThread>
#include <thread>
#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include  <v1/commonapi/HelloWorldProxy.hpp>
#include <unistd.h>
#include <ConnectEvent.h>


class RegisterCommonapi : public QThread
{
private:
    std::shared_ptr<v1::commonapi::HelloWorldProxy<>> myProxy;
public:
    RegisterCommonapi();

protected:
    void run() override;

public:
    void init();

};

#endif // REGISTERCOMMONAPI_H
