/*
 * Generated by gdbus-codegen-glibmm 2.42.0. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#include "./vrttsipc_proxy.h"

#include <utility>

template <class T>
inline T specialGetter(Glib::Variant<T> variant)
{
    return variant.get();
}

template <>
inline std::string specialGetter(Glib::Variant<std::string> variant)
{
    // String is not guaranteed to be null-terminated, so don't use ::get()
    gsize n_elem;
    gsize elem_size = sizeof(char);
    char *data = (char *)g_variant_get_fixed_array(variant.gobj(), &n_elem, elem_size);

    return std::string(data, n_elem);
}

void ccos::core::vrttsipcProxy::proxySendMessage(
    const Glib::ustring &arg_msgId,
    const Glib::ustring &arg_message,
    const Gio::SlotAsyncReady &callback,
    const Glib::RefPtr<Gio::Cancellable> &cancellable,
    int timeout_msec)
{
    Glib::VariantContainerBase base;
    base = vrttsipcTypeWrap::proxySendMessage_pack(
        arg_msgId,
        arg_message);

    m_proxy->call("proxySendMessage", callback, cancellable, base, timeout_msec);
}

void ccos::core::vrttsipcProxy::proxySendMessage_finish(
    const Glib::RefPtr<Gio::AsyncResult> &result)
{
    Glib::VariantContainerBase wrapped;
    wrapped = m_proxy->call_finish(result);
}

void ccos::core::vrttsipcProxy::proxySendMessage_sync(
    const Glib::ustring &arg_msgId,
    const Glib::ustring &arg_message,
    const Glib::RefPtr<Gio::Cancellable> &cancellable,
    int timeout_msec)
{
    Glib::VariantContainerBase base;
    base = vrttsipcTypeWrap::proxySendMessage_pack(
        arg_msgId,
        arg_message);

    Glib::VariantContainerBase wrapped;
    wrapped = m_proxy->call_sync("proxySendMessage", cancellable, base, timeout_msec);
}

void ccos::core::vrttsipcProxy::handle_signal(const Glib::ustring & /* sender_name */,
                                              const Glib::ustring &signal_name,
                                              const Glib::VariantContainerBase &parameters)
{
    static_cast<void>(signal_name); // maybe unused
    static_cast<void>(parameters);  // maybe unused
    if (signal_name == "stubSendMessage")
    {
        if (parameters.get_n_children() != 2)
            return;
        Glib::Variant<Glib::ustring> base_msgId;
        parameters.get_child(base_msgId, 0);
        Glib::ustring p_msgId;
        p_msgId = base_msgId.get();

        if (parameters.get_n_children() != 2)
            return;
        Glib::Variant<Glib::ustring> base_message;
        parameters.get_child(base_message, 1);
        Glib::ustring p_message;
        p_message = base_message.get();

        stubSendMessage_signal.emit((p_msgId), (p_message));
    }
}

void ccos::core::vrttsipcProxy::handle_properties_changed(
    const Gio::DBus::Proxy::MapChangedProperties &changed_properties,
    const std::vector<Glib::ustring> & /* invalidated_properties */)
{
    static_cast<void>(changed_properties); // maybe unused

    // Only check changed_properties since value will already be cached. Glib can be setup to get
    // values of invalidated properties in which case property will be in changed_properties when
    // value is actually received. See Gio::DBus::ProxyFlags::PROXY_FLAGS_GET_INVALIDATED_PROPERTIES .
}

ccos::core::vrttsipcProxy::vrttsipcProxy(const Glib::RefPtr<Gio::DBus::Proxy> &proxy) : m_proxy(proxy)
{
    m_proxy->signal_signal().connect(sigc::mem_fun(this, &vrttsipcProxy::handle_signal));
    m_proxy->signal_properties_changed().connect(sigc::mem_fun(this, &vrttsipcProxy::handle_properties_changed));
}

void ccos::core::vrttsipcProxy::createForBus(
    Gio::DBus::BusType busType,
    Gio::DBus::ProxyFlags proxyFlags,
    const std::string &name,
    const std::string &objectPath,
    const Gio::SlotAsyncReady &slot,
    const Glib::RefPtr<Gio::Cancellable> &cancellable)
{
    Gio::DBus::Proxy::create_for_bus(busType,
                                     name,
                                     objectPath,
                                     "ccos.core.vrttsipc",
                                     slot,
                                     cancellable,
                                     Glib::RefPtr<Gio::DBus::InterfaceInfo>(),
                                     proxyFlags);
}

Glib::RefPtr<ccos::core::vrttsipcProxy> ccos::core::vrttsipcProxy::createForBusFinish(const Glib::RefPtr<Gio::AsyncResult> &result)
{
    Glib::RefPtr<Gio::DBus::Proxy> proxy =
        Gio::DBus::Proxy::create_for_bus_finish(result);
    ccos::core::vrttsipcProxy *p =
        new ccos::core::vrttsipcProxy(proxy);
    return Glib::RefPtr<ccos::core::vrttsipcProxy>(p);
}

Glib::RefPtr<ccos::core::vrttsipcProxy> ccos::core::vrttsipcProxy::createForBus_sync(
    Gio::DBus::BusType busType,
    Gio::DBus::ProxyFlags proxyFlags,
    const std::string &name,
    const std::string &objectPath,
    const Glib::RefPtr<Gio::Cancellable> &cancellable)
{
    Glib::RefPtr<Gio::DBus::Proxy> proxy =
        Gio::DBus::Proxy::create_for_bus_sync(busType,
                                              name,
                                              objectPath,
                                              "ccos.core.vrttsipc",
                                              cancellable,
                                              Glib::RefPtr<Gio::DBus::InterfaceInfo>(),
                                              proxyFlags);
    ccos::core::vrttsipcProxy *p =
        new ccos::core::vrttsipcProxy(proxy);
    printf("vrttsipcProxy pointer: [%p]\n", p);
    return Glib::RefPtr<ccos::core::vrttsipcProxy>(p);
}
