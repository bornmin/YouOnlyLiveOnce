#include <Common.h>
#include <vrttsipc_proxy.h>

using namespace ccos::core;

class DBusProxy : public std::enable_shared_from_this<DBusProxy>
{
public:
    DBusProxy();
    virtual ~DBusProxy();

    void init();

    void deinit();

    void sendMessage(const string &msgId, const string &msg);

    void onMessageReceived(const string msgId, const string msg);

private:
    bool isMainLoopExist();

    Glib::RefPtr<Glib::MainLoop> getMainLoop();

    static void loop(DBusProxy *object);

private:
    std::thread mThread;
    bool m_bMainLoopExist;
    Glib::RefPtr<Glib::MainLoop> m_Mainloop;
    Glib::RefPtr<vrttsipcProxy> m_dbusProxy;
    sigc::connection m_Connection;
};