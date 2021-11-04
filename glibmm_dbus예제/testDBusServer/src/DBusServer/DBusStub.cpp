#include <DBusStub.h>

class vrttsipcStubImpl : public vrttsipcStub
{
public:
    void proxySendMessage(const Glib::ustring &msgId,
                          const Glib::ustring &message,
                          MethodInvocation &invocation) override // vrttsipcStub 클래스에서 상속받은 함수로 sync call을 받을 함수이다.
    {
        printf("\n################Get Client Message!!!!! ##################\n ");
        printf("msgId : [%s] message : [%s] \n", msgId.c_str(), message.c_str());
        printf("#####################################3####################\n\n ");

        m_IPC->onMessageReceived(msgId, message);

        invocation.ret(); //sync call 에 대한 return return 안해주면 client에서 계속 대기함
    }

    void stubSendMessage(const Glib::ustring &msgId, const Glib::ustring &message)
    {
        printf("stubSendMessage msgId [%s] message : [%s]\n", msgId.c_str(), message.c_str());
        vector<Glib::ustring> destination;
        string sessionId = "test";
        printf("msgId : [%s] from [%s] \n", msgId.c_str(), message.c_str());

        std::vector<Glib::ustring> destination_bus_names;
        destination_bus_names.push_back("");
        stubSendMessage_signal.emit(msgId, message); //broad cast 날림 (broad cast는 모든 client에 날린다.)
        printf("stubSendMessage emit end!!!\n");
    }

private:
    shared_ptr<DBusStub> m_IPC;
};

DBusStub::DBusStub()
{
    printf("DBusStub() called \n");
    m_bMainLoopExist = false;
    Glib::init(); //꼭 해줘야함
    Gio::init();  //꼭 해줘야함
}

DBusStub::~DBusStub()
{
}

void DBusStub::init(bool bmakeTrhead)
{
    printf("--------------------------------- init() -----------------------------\n");

    m_impl = make_unique<vrttsipcStubImpl>();
    m_Mainloop = Glib::MainLoop::create();
    m_bMainLoopExist = true;
    m_connectionId = Gio::DBus::own_name( //dbus 정보를 등록
        Gio::DBus::BUS_TYPE_SESSION, VRTTSIPC_DBUS_INTERFACE,
        [&](const Glib::RefPtr<Gio::DBus::Connection> &connection, const Glib::ustring &name)
        {
            printf("Connected to bus name: [%s]\n", name.c_str());
            if (m_impl->register_object(connection, VRTTSIPC_DBUS_PATH) == 0)
            {
                printf("Connected to bus Failed");
            }
        },
        [&](const Glib::RefPtr<Gio::DBus::Connection> &connection, const Glib::ustring &name)
        {
            printf("Name acquired %s\n", name.c_str());
        },
        [&](const Glib::RefPtr<Gio::DBus::Connection> &, const Glib::ustring &)
        {
            printf("Name lost\n");
            m_Mainloop->quit();
        });

    if (!m_connectionId)
    {
        printf("identifier cannot be 0");
    }

    mThread = std::thread(DBusStub::loop, this);

    printf("---------------------  init() end  ---------------------------\n");
}

void DBusStub::deinit()
{
    printf("------------------------ deinit  ------------------------\n");
    m_bMainLoopExist = false;
    m_Mainloop->quit();
    Gio::DBus::unown_name(m_connectionId);
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

void DBusStub::sendMessage(const string &msgId, const string &msg)
{
    printf("sendMessage msgId: [%s] msg :[%s] \n", msgId.c_str(), msg.c_str());
    return m_impl->stubSendMessage(msgId, msg);
}

void DBusStub::onMessageReceived(const string &msgId, const string &msg)
{
    printf("onMessageReceived msgId: [%s] msg: [%s]\n", msgId.c_str(), msg.c_str());
}

bool DBusStub::isMainLoopExist()
{
    return m_bMainLoopExist;
}

Glib::RefPtr<Glib::MainLoop> DBusStub::getMainLoop()
{
    return m_Mainloop;
}

void DBusStub::loop(DBusStub *object)
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
