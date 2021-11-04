#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <glibmm.h>
#include <giomm.h>
#include "./vrttsipc_common.h"

namespace ccos
{
    namespace core
    {

        class vrttsipcProxy : public Glib::ObjectBase
        {
        public:
            static void createForBus(Gio::DBus::BusType busType,
                                     Gio::DBus::ProxyFlags proxyFlags,
                                     const std::string &name,
                                     const std::string &objectPath,
                                     const Gio::SlotAsyncReady &slot,
                                     const Glib::RefPtr<Gio::Cancellable> &cancellable = {});

            static Glib::RefPtr<vrttsipcProxy> createForBusFinish(const Glib::RefPtr<Gio::AsyncResult> &result);

            static Glib::RefPtr<vrttsipcProxy> createForBus_sync(
                Gio::DBus::BusType busType,
                Gio::DBus::ProxyFlags proxyFlags,
                const std::string &name,
                const std::string &objectPath,
                const Glib::RefPtr<Gio::Cancellable> &cancellable = {});

            Glib::RefPtr<Gio::DBus::Proxy> dbusProxy() const { return m_proxy; }

            void proxySendMessage(
                const Glib::ustring &msgId,
                const Glib::ustring &message,
                const Gio::SlotAsyncReady &slot,
                const Glib::RefPtr<Gio::Cancellable> &cancellable = {},
                int timeout_msec = -1);

            void proxySendMessage_finish(
                const Glib::RefPtr<Gio::AsyncResult> &res);

            void
            proxySendMessage_sync(
                const Glib::ustring &msgId, const Glib::ustring &message, const Glib::RefPtr<Gio::Cancellable> &cancellable = {},
                int timeout_msec = -1);

            sigc::signal<void, Glib::ustring, Glib::ustring> stubSendMessage_signal;

            void reference() const override {}
            void unreference() const override {}

        protected:
            Glib::RefPtr<Gio::DBus::Proxy> m_proxy;

        private:
            vrttsipcProxy(const Glib::RefPtr<Gio::DBus::Proxy> &proxy);

            void handle_signal(const Glib::ustring &sender_name,
                               const Glib::ustring &signal_name,
                               const Glib::VariantContainerBase &parameters);

            void handle_properties_changed(const Gio::DBus::Proxy::MapChangedProperties &changed_properties,
                                           const std::vector<Glib::ustring> &invalidated_properties);
        };

    } // core
} // ccos
