#pragma once
#include <iostream>
#include <vector>
#include "glibmm.h"
#include "giomm.h"

namespace ccos {
namespace core {

class vrttsipcTypeWrap {
public:
    template<typename T>
    static void unwrapList(std::vector<T> &list, const Glib::VariantContainerBase &wrapped) {
        for (uint i = 0; i < wrapped.get_n_children(); i++) {
            Glib::Variant<T> item;
            wrapped.get_child(item, i);
            list.push_back(item.get());
        }
    }

    static std::vector<Glib::ustring> stdStringVecToGlibStringVec(const std::vector<std::string> &strv) {
        std::vector<Glib::ustring> newStrv;
        for (uint i = 0; i < strv.size(); i++) {
            newStrv.push_back(strv[i]);
        }

        return newStrv;
    }

    static std::vector<std::string> glibStringVecToStdStringVec(const std::vector<Glib::ustring> &strv) {
        std::vector<std::string> newStrv;
        for (uint i = 0; i < strv.size(); i++) {
            newStrv.push_back(strv[i]);
        }

        return newStrv;
    }

    static Glib::VariantContainerBase proxySendMessage_pack(
        const Glib::ustring & arg_msgId,
        const Glib::ustring & arg_message) {
        Glib::VariantContainerBase base;
        std::vector<Glib::VariantBase> params;

        Glib::Variant<Glib::ustring> msgId_param =
            Glib::Variant<Glib::ustring>::create(arg_msgId);
        params.push_back(msgId_param);

        Glib::Variant<Glib::ustring> message_param =
            Glib::Variant<Glib::ustring>::create(arg_message);
        params.push_back(message_param);
        return Glib::VariantContainerBase::create_tuple(params);
    }
};

} // core
} // ccos


