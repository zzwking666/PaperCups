#pragma once

#include"rwul/oso/oso_core.h"
#include <string>

namespace cdm {
    class PaperCupsInfo
    {
    public:
        PaperCupsInfo() = default;
        ~PaperCupsInfo() = default;

        PaperCupsInfo(const rw::oso::ObjectStoreAssembly& assembly);
        PaperCupsInfo(const PaperCupsInfo& obj);

        PaperCupsInfo& operator=(const PaperCupsInfo& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const PaperCupsInfo& obj) const;
        bool operator!=(const PaperCupsInfo& obj) const;

    public:
        int shengchanzongliang{ 0 };
        int feipinzongliang{ 0 };
        int shengchanzongliang2{ 0 };
        int feipinzongliang2{ 0 };
    };

    inline PaperCupsInfo::PaperCupsInfo(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$PaperCupsInfo$")
        {
            throw std::runtime_error("Assembly is not $class$PaperCupsInfo$");
        }
        auto shengchanzongliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shengchanzongliang$"));
        if (!shengchanzongliangItem) {
            throw std::runtime_error("$variable$shengchanzongliang is not found");
        }
        shengchanzongliang = shengchanzongliangItem->getValueAsInt();
        auto feipinzongliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$feipinzongliang$"));
        if (!feipinzongliangItem) {
            throw std::runtime_error("$variable$feipinzongliang is not found");
        }
        feipinzongliang = feipinzongliangItem->getValueAsInt();
        auto shengchanzongliang2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shengchanzongliang2$"));
        if (!shengchanzongliang2Item) {
            throw std::runtime_error("$variable$shengchanzongliang2 is not found");
        }
        shengchanzongliang2 = shengchanzongliang2Item->getValueAsInt();
        auto feipinzongliang2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$feipinzongliang2$"));
        if (!feipinzongliang2Item) {
            throw std::runtime_error("$variable$feipinzongliang2 is not found");
        }
        feipinzongliang2 = feipinzongliang2Item->getValueAsInt();
    }

    inline PaperCupsInfo::PaperCupsInfo(const PaperCupsInfo& obj)
    {
        shengchanzongliang = obj.shengchanzongliang;
        feipinzongliang = obj.feipinzongliang;
        shengchanzongliang2 = obj.shengchanzongliang2;
        feipinzongliang2 = obj.feipinzongliang2;
    }

    inline PaperCupsInfo& PaperCupsInfo::operator=(const PaperCupsInfo& obj)
    {
        if (this != &obj) {
            shengchanzongliang = obj.shengchanzongliang;
            feipinzongliang = obj.feipinzongliang;
            shengchanzongliang2 = obj.shengchanzongliang2;
            feipinzongliang2 = obj.feipinzongliang2;
        }
        return *this;
    }

    inline PaperCupsInfo::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$PaperCupsInfo$");
        auto shengchanzongliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shengchanzongliangItem->setName("$variable$shengchanzongliang$");
        shengchanzongliangItem->setValueFromInt(shengchanzongliang);
        assembly.addItem(shengchanzongliangItem);
        auto feipinzongliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        feipinzongliangItem->setName("$variable$feipinzongliang$");
        feipinzongliangItem->setValueFromInt(feipinzongliang);
        assembly.addItem(feipinzongliangItem);
        auto shengchanzongliang2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        shengchanzongliang2Item->setName("$variable$shengchanzongliang2$");
        shengchanzongliang2Item->setValueFromInt(shengchanzongliang2);
        assembly.addItem(shengchanzongliang2Item);
        auto feipinzongliang2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        feipinzongliang2Item->setName("$variable$feipinzongliang2$");
        feipinzongliang2Item->setValueFromInt(feipinzongliang2);
        assembly.addItem(feipinzongliang2Item);
        return assembly;
    }

    inline bool PaperCupsInfo::operator==(const PaperCupsInfo& obj) const
    {
        return shengchanzongliang == obj.shengchanzongliang && feipinzongliang == obj.feipinzongliang && shengchanzongliang2 == obj.shengchanzongliang2 && feipinzongliang2 == obj.feipinzongliang2;
    }

    inline bool PaperCupsInfo::operator!=(const PaperCupsInfo& obj) const
    {
        return !(*this == obj);
    }

}

