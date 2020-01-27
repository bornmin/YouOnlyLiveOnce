cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

include_directories(
    src-gen
    ../capicxx-core-runtime/include
    ../capicxx-someip-runtime/include
    ../vSomeIP/interface
    )

link_directories(
    /home/shin/commonapi-someip/capicxx-core-runtime/build
    /home/shin/commonapi-someip/capicxx-someip-runtime/build
    /home/shin/commonapi-someip/vSomeIP/build
    )

add_executable(HelloWorldClient
    src/HelloWorldClient.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPProxy.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPDeployment.cpp
    )
target_link_libraries(HelloWorldClient CommonAPI CommonAPI-SomeIP vsomeip)

add_executable(HelloWorldService
    src/HelloWorldService.cpp
    src/HelloWorldStubImpl.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPStubAdapter.cpp
    src-gen/v1/commonapi/HelloWorldStubDefault.cpp
    src-gen/v1/commonapi/HelloWorldSomeIPDeployment.cpp
    )
target_link_libraries(HelloWorldService CommonAPI CommonAPI-SomeIP vsomeip) 
