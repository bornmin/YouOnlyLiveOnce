#pragma once
#include <string>
#include <vector>
#include <glibmm.h>
#include <giomm.h>
#include "./vrttsipc_common.h"

namespace ccos {
namespace core {

class vrttsipcStub : public sigc::trackable {
public:
    vrttsipcStub();
    virtual ~vrttsipcStub();

    vrttsipcStub(const vrttsipcStub &other) = delete;
    vrttsipcStub(vrttsipcStub &&other) = delete;
    vrttsipcStub &operator=(const vrttsipcStub &other) = delete;
    vrttsipcStub &operator=(vrttsipcStub &&other) = delete;

    guint register_object(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                          const Glib::ustring &object_path);
    void unregister_object();

    unsigned int usage_count() const {
        return static_cast<unsigned int>(m_registered_objects.size());
    }

    class MethodInvocation;

protected:
    virtual void proxySendMessage(
        const Glib::ustring & msgId,
        const Glib::ustring & message,
        MethodInvocation &invocation) = 0;

    void stubSendMessage_emitter(const std::vector<Glib::ustring> &destination_bus_names, const Glib::ustring &, const Glib::ustring &);
    sigc::signal<void, const Glib::ustring &, const Glib::ustring &> stubSendMessage_signal;
    sigc::signal<void, const std::vector<Glib::ustring>&, const Glib::ustring &, const Glib::ustring &> stubSendMessage_selectiveSignal;

    void on_method_call(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                        const Glib::ustring &sender,
                        const Glib::ustring &object_path,
                        const Glib::ustring &interface_name,
                        const Glib::ustring &method_name,
                        const Glib::VariantContainerBase &parameters,
                        const Glib::RefPtr<Gio::DBus::MethodInvocation> &invocation);

    void on_interface_get_property(Glib::VariantBase& property,
                                   const Glib::RefPtr<Gio::DBus::Connection> &connection,
                                   const Glib::ustring &sender,
                                   const Glib::ustring &object_path,
                                   const Glib::ustring &interface_name,
                                   const Glib::ustring &property_name);

    bool on_interface_set_property(
        const Glib::RefPtr<Gio::DBus::Connection> &connection,
        const Glib::ustring &sender,
        const Glib::ustring &object_path,
        const Glib::ustring &interface_name,
        const Glib::ustring &property_name,
        const Glib::VariantBase &value);

private:
    bool emitSignal(const std::string &propName, Glib::VariantBase &value);

    struct RegisteredObject {
        guint id;
        Glib::RefPtr<Gio::DBus::Connection> connection;
        std::string object_path;
    };

    Glib::RefPtr<Gio::DBus::NodeInfo> introspection_data;
    std::vector<RegisteredObject> m_registered_objects;
    std::string m_interfaceName;
};

class vrttsipcStub::MethodInvocation {
public:
    MethodInvocation(const Glib::RefPtr<Gio::DBus::MethodInvocation> &msg):
        m_message(msg) {}

    const Glib::RefPtr<Gio::DBus::MethodInvocation> getMessage() {
        return m_message;
    }

    void ret(Glib::Error error) {
        m_message->return_error(error);
    }

    void returnError(const Glib::ustring &domain, int code, const Glib::ustring &message) {
        m_message->return_error(domain, code, message);
    }

    void ret() {
        std::vector<Glib::VariantBase> vlist;

        m_message->return_value(Glib::Variant<Glib::VariantBase>::create_tuple(vlist));
    }

private:
    Glib::RefPtr<Gio::DBus::MethodInvocation> m_message;
};

} // core
} // ccos

