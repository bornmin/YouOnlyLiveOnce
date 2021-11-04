#include <Common.h>
#include <vrttsipc_stub.h>

using namespace ccos::core;

class vrttsipcStubImpl;

class DBusStub : public std::enable_shared_from_this<DBusStub>
{
public:
    DBusStub();
    virtual ~DBusStub();

    void init(bool bmakeTrhead = true);

    void deinit();

    void sendMessage(const string &msgId, const string &msg);

    void onMessageReceived(const string &msgId, const string &msg);

private:
    bool isMainLoopExist();

    Glib::RefPtr<Glib::MainLoop> getMainLoop();

    static void loop(DBusStub *object);

private:
    std::thread mThread;

    bool m_bMainLoopExist;

    Glib::RefPtr<Glib::MainLoop> m_Mainloop;

    unique_ptr<vrttsipcStubImpl> m_impl;

    guint m_connectionId = 0;
};
