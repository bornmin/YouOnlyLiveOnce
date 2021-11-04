static const char interfaceXml0[] = R"XML_DELIMITER(<node>
  <interface name="ccos.core.vrttsipc">
    <method name="proxySendMessage">
        <arg name="msgId" direction="in" type ="s"/>
        <arg name="message" direction="in" type ="s"/>
    </method>
    <signal name="stubSendMessage">
        <arg name="msgId" type ="s"/>
        <arg name="message" type ="s"/>
    </signal>
  </interface>
</node>
)XML_DELIMITER";

#include "./vrttsipc_stub.h"

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

ccos::core::vrttsipcStub::vrttsipcStub() : m_interfaceName("ccos.core.vrttsipc")
{
    stubSendMessage_signal.connect(sigc::bind<0>(sigc::mem_fun(this, &vrttsipcStub::stubSendMessage_emitter),
                                                 std::vector<Glib::ustring>({""})));
    stubSendMessage_selectiveSignal.connect(sigc::mem_fun(this, &vrttsipcStub::stubSendMessage_emitter));
}

ccos::core::vrttsipcStub::~vrttsipcStub()
{
    unregister_object();
}

guint ccos::core::vrttsipcStub::register_object(
    const Glib::RefPtr<Gio::DBus::Connection> &connection,
    const Glib::ustring &object_path)
{
    if (!introspection_data)
    {
        try
        {
            introspection_data = Gio::DBus::NodeInfo::create_for_xml(interfaceXml0);
        }
        catch (const Glib::Error &ex)
        {
            g_warning("Unable to create introspection data for %s: %s", object_path.c_str(), ex.what().c_str());
            return 0;
        }
    }

    Gio::DBus::InterfaceVTable *interface_vtable =
        new Gio::DBus::InterfaceVTable(
            sigc::mem_fun(this, &vrttsipcStub::on_method_call),
            sigc::mem_fun(this, &vrttsipcStub::on_interface_get_property),
            sigc::mem_fun(this, &vrttsipcStub::on_interface_set_property));

    guint registration_id;
    try
    {
        registration_id = connection->register_object(object_path,
                                                      introspection_data->lookup_interface("ccos.core.vrttsipc"),
                                                      *interface_vtable);
    }
    catch (const Glib::Error &ex)
    {
        g_warning("Registration of object %s failed: %s", object_path.c_str(), ex.what().c_str());
        return 0;
    }

    m_registered_objects.emplace_back(RegisteredObject{
        registration_id,
        connection,
        object_path});

    return registration_id;
}

void ccos::core::vrttsipcStub::unregister_object()
{
    for (const RegisteredObject &obj : m_registered_objects)
    {
        obj.connection->unregister_object(obj.id);
    }
    m_registered_objects.clear();
}

void ccos::core::vrttsipcStub::on_method_call(
    const Glib::RefPtr<Gio::DBus::Connection> & /* connection */,
    const Glib::ustring & /* sender */,
    const Glib::ustring & /* object_path */,
    const Glib::ustring & /* interface_name */,
    const Glib::ustring &method_name,
    const Glib::VariantContainerBase &parameters,
    const Glib::RefPtr<Gio::DBus::MethodInvocation> &invocation)
{
    static_cast<void>(method_name); // maybe unused
    static_cast<void>(parameters);  // maybe unused
    static_cast<void>(invocation);  // maybe unused

    if (method_name.compare("proxySendMessage") == 0)
    {
        Glib::Variant<Glib::ustring> base_msgId;
        parameters.get_child(base_msgId, 0);
        Glib::ustring p_msgId = specialGetter(base_msgId);

        Glib::Variant<Glib::ustring> base_message;
        parameters.get_child(base_message, 1);
        Glib::ustring p_message = specialGetter(base_message);

        MethodInvocation methodInvocation(invocation);
        proxySendMessage(
            (p_msgId),
            (p_message),
            methodInvocation);
    }
}

void ccos::core::vrttsipcStub::on_interface_get_property(
    Glib::VariantBase &property,
    const Glib::RefPtr<Gio::DBus::Connection> & /* connection */,
    const Glib::ustring & /* sender */,
    const Glib::ustring & /* object_path */,
    const Glib::ustring & /* interface_name */,
    const Glib::ustring &property_name)
{
    static_cast<void>(property);      // maybe unused
    static_cast<void>(property_name); // maybe unused
}

bool ccos::core::vrttsipcStub::on_interface_set_property(
    const Glib::RefPtr<Gio::DBus::Connection> & /* connection */,
    const Glib::ustring & /* sender */,
    const Glib::ustring & /* object_path */,
    const Glib::ustring & /* interface_name */,
    const Glib::ustring &property_name,
    const Glib::VariantBase &value)
{
    static_cast<void>(property_name); // maybe unused
    static_cast<void>(value);         // maybe unused

    return true;
}

void ccos::core::vrttsipcStub::stubSendMessage_emitter(
    const std::vector<Glib::ustring> &destination_bus_names, const Glib::ustring &msgId, const Glib::ustring &message)
{
    std::vector<Glib::VariantBase> paramsList;

    paramsList.push_back(Glib::Variant<Glib::ustring>::create((msgId)));
    ;
    paramsList.push_back(Glib::Variant<Glib::ustring>::create((message)));
    ;

    const Glib::VariantContainerBase params =
        Glib::Variant<std::vector<Glib::VariantBase>>::create_tuple(paramsList);
    for (const RegisteredObject &obj : m_registered_objects)
    {
        for (const auto &bus_name : destination_bus_names)
        {
            obj.connection->emit_signal(
                obj.object_path,
                "ccos.core.vrttsipc",
                "stubSendMessage",
                bus_name,
                params);
        }
    }
}

bool ccos::core::vrttsipcStub::emitSignal(
    const std::string &propName,
    Glib::VariantBase &value)
{
    std::map<Glib::ustring, Glib::VariantBase> changedProps;
    std::vector<Glib::ustring> changedPropsNoValue;

    changedProps[propName] = value;

    Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>> changedPropsVar =
        Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(changedProps);
    Glib::Variant<std::vector<Glib::ustring>> changedPropsNoValueVar =
        Glib::Variant<std::vector<Glib::ustring>>::create(changedPropsNoValue);
    std::vector<Glib::VariantBase> ps;
    ps.push_back(Glib::Variant<Glib::ustring>::create(m_interfaceName));
    ps.push_back(changedPropsVar);
    ps.push_back(changedPropsNoValueVar);
    Glib::VariantContainerBase propertiesChangedVariant =
        Glib::Variant<std::vector<Glib::VariantBase>>::create_tuple(ps);

    for (const RegisteredObject &obj : m_registered_objects)
    {
        obj.connection->emit_signal(
            obj.object_path,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            Glib::ustring(),
            propertiesChangedVariant);
    }

    return true;
}
