#include <DBusProxy.h>

DBusProxy::DBusProxy()
{
    m_bMainLoopExist = false;
    Glib::init(); //꼭 해줘야함
    Gio::init();  //꼭 해줘야함
    try
    {
    }
    catch (Gio::DBus::Error &e)
    {
        printf("test %s", e.what().c_str());
    }
}

DBusProxy::~DBusProxy()
{
}

void DBusProxy::init()
{
    printf("--------------------------------- init() -----------------------------\n");
    m_dbusProxy = vrttsipcProxy::createForBus_sync(Gio::DBus::BUS_TYPE_SESSION, Gio::DBus::PROXY_FLAGS_NONE,
                                                   VRTTSIPC_DBUS_INTERFACE, VRTTSIPC_DBUS_PATH);
    m_Connection = m_dbusProxy->stubSendMessage_signal.connect(sigc::mem_fun(this, &DBusProxy::onMessageReceived)); // 서버에서 날린 signal을 함수로 매칭 시킨다. (signal 에대한 callback함수 선언)
    //vrttsipcProxy *value = m_dbusProxy.get();
   // printf("value: [%p]\n", value);
    m_Mainloop = Glib::MainLoop::create();
    m_bMainLoopExist = true;
    mThread = std::thread(DBusProxy::loop, this);
    printf("---------------------  init() end  ---------------------------\n");
}

void DBusProxy::deinit()
{
    printf("------------------------ deinit  ------------------------\n");
    m_bMainLoopExist = false;
    m_Connection.disconnect();
    //printf("before reset m_dbusProxy pointer: [%p]\n", m_dbusProxy.get());
    m_dbusProxy.reset();
    //printf("after reset m_dbusProxy pointer: [%p]\n", m_dbusProxy.get());
    m_Mainloop->quit();

    //m_dbusProxy->stubSendMessage_signal.disconnect(); // 서버에서 날린 signal을 함수로 매칭 시킨다. (signal 에대한 callback함수 선언)
    if (mThread.joinable())
    {
        printf("mThread.join()!!!!!!!! \n");
        mThread.join();
    }
    if (mThread.joinable()) //스레드가 잘 종료 되었는지 확인
    {
        printf("mThread.joinable()!!!!!!!! \n");
    }
    printf("------------------- deinit end -------------------\n");
}

void DBusProxy::sendMessage(const string &msgId, const string &msg)
{
    printf("sendMessage called!!");
    try
    {
        if (isMainLoopExist())
        {
            printf("sendMessage msgId: [%s] msg :[%s]\n", msgId.c_str(), msg.c_str());
            m_dbusProxy->proxySendMessage_sync(Glib::ustring(msgId), Glib::ustring(msg));
        }
        else
        {
            printf("not sendMessage!!! ");
        }
    }
    catch (Gio::DBus::Error &e)
    {
        printf("[%s]\n", e.what().c_str());
    }
}

void DBusProxy::onMessageReceived(const string msgId, const string msg)
{
    printf("\n################Get Server Message!!!!! ##################\n ");
    printf("msgId: [%s] msg: [%s]\n", msgId.c_str(), msg.c_str());
    printf("#####################################3####################\n\n  ");
}

bool DBusProxy::isMainLoopExist()
{
    return m_bMainLoopExist;
}

Glib::RefPtr<Glib::MainLoop> DBusProxy::getMainLoop()
{
    return m_Mainloop;
}

void DBusProxy::loop(DBusProxy *object)
{
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  loop called   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2\n");
    if (!object->getMainLoop()->is_running())
    {
        while (object->isMainLoopExist())
        {
            printf("while!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            object->getMainLoop()->run(); //main loop에서 쓰레드를 잡고있음
        }
    }
}
