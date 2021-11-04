cmake_minimum_required(VERSION 3.1)
project(testDBusServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Werror -Wno-error=unused-function -pthread")

find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLIB REQUIRED glib-2.0)
    pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)
    pkg_check_modules(GIOMM REQUIRED giomm-2.4)


set(CLIENT_APP_NAME testDBusClient)
set(CLIENT_LIB_NAME testDBus)


list(
    APPEND
    CLIENT_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DbusClient/testGDbusClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DbusClient/DBusProxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Glibmm/vrttsipc_proxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Glibmm/vrttsipc_common.cpp
)

list(
    APPEND
    CLIENT_INCLUDE_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DbusClient
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Glibmm
)

 include_directories(${CLIENT_LIB_NAME} PRIVATE ${CLIENT_INCLUDE_DIRECTORY} ${GLIB_INCLUDE_DIRS} ${GLIBMM_INCLUDE_DIRS} ${GIOMM_INCLUDE_DIRS})
 #link_libraries(${CLIENT_LIB_NAME} ${GLIBMM_LDFLAGS} ${GIOMM_LDFLAGS}) 

add_library(${CLIENT_LIB_NAME} SHARED ${CLIENT_INCLUDE_DIRECTORY} ${CLIENT_SOURCE_FILES})

add_executable(${CLIENT_APP_NAME}
    ${CLIENT_SOURCE_FILES}
)

target_include_directories(${CLIENT_APP_NAME} PRIVATE ${CLIENT_INCLUDE_DIRECTORY} ${GLIB_INCLUDE_DIRS} ${GLIBMM_INCLUDE_DIRS} ${GIOMM_INCLUDE_DIRS})
target_link_libraries(${CLIENT_APP_NAME} ${GLIBMM_LDFLAGS} ${GIOMM_LDFLAGS} ) 





set(SERVER_APP_NAME testDBusServer)
 
list(
    APPEND
    SERVER_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DBusServer/testGDbusServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DBusServer/DBusStub.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Glibmm/vrttsipc_stub.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Glibmm/vrttsipc_common.cpp
)

list(
    APPEND
    SERVER_INCLUDE_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DBusServer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Glibmm
)

add_executable(${SERVER_APP_NAME}
    ${SERVER_SOURCE_FILES}
)

target_include_directories(${SERVER_APP_NAME} PRIVATE ${SERVER_INCLUDE_DIRECTORY} ${GLIB_INCLUDE_DIRS} ${GLIBMM_INCLUDE_DIRS} ${GIOMM_INCLUDE_DIRS})

target_link_libraries(${SERVER_APP_NAME} ${GLIBMM_LDFLAGS} ${GIOMM_LDFLAGS})


