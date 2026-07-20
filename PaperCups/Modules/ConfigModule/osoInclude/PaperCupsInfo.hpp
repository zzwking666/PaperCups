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
    }

    inline PaperCupsInfo::PaperCupsInfo(const PaperCupsInfo& obj)
    {
        shengchanzongliang = obj.shengchanzongliang;
        feipinzongliang = obj.feipinzongliang;
    }

    inline PaperCupsInfo& PaperCupsInfo::operator=(const PaperCupsInfo& obj)
    {
        if (this != &obj) {
            shengchanzongliang = obj.shengchanzongliang;
            feipinzongliang = obj.feipinzongliang;
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
        return assembly;
    }

    inline bool PaperCupsInfo::operator==(const PaperCupsInfo& obj) const
    {
        return shengchanzongliang == obj.shengchanzongliang && feipinzongliang == obj.feipinzongliang;
    }

    inline bool PaperCupsInfo::operator!=(const PaperCupsInfo& obj) const
    {
        return !(*this == obj);
    }

}

