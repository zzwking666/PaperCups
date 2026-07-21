#pragma once

#include"rwul/oso/oso_core.h"
#include <string>

namespace cdm {
    class SetConfig
    {
    public:
        SetConfig() = default;
        ~SetConfig() = default;

        SetConfig(const rw::oso::ObjectStoreAssembly& assembly);
        SetConfig(const SetConfig& obj);

        SetConfig& operator=(const SetConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const SetConfig& obj) const;
        bool operator!=(const SetConfig& obj) const;

    public:
        int zengyi{ 0 };
        int baoguang{ 0 };
        double xiangsudangliang{ 0 };
        int shangxianwei{ 0 };
        int xiaxianwei{ 0 };
        int zuoxianwei{ 0 };
        int youxianwei{ 0 };
        int tifeiyanshi{ 0 };
        int tifeishuchuchixushijian{ 0 };
        int xiangjichutujiange{ 0 };
    };

    inline SetConfig::SetConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$SetConfig$")
        {
            throw std::runtime_error("Assembly is not $class$SetConfig$");
        }
        auto zengyiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zengyi$"));
        if (!zengyiItem) {
            throw std::runtime_error("$variable$zengyi is not found");
        }
        zengyi = zengyiItem->getValueAsInt();
        auto baoguangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$baoguang$"));
        if (!baoguangItem) {
            throw std::runtime_error("$variable$baoguang is not found");
        }
        baoguang = baoguangItem->getValueAsInt();
        auto xiangsudangliangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangsudangliang$"));
        if (!xiangsudangliangItem) {
            throw std::runtime_error("$variable$xiangsudangliang is not found");
        }
        xiangsudangliang = xiangsudangliangItem->getValueAsDouble();
        auto shangxianweiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shangxianwei$"));
        if (!shangxianweiItem) {
            throw std::runtime_error("$variable$shangxianwei is not found");
        }
        shangxianwei = shangxianweiItem->getValueAsInt();
        auto xiaxianweiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiaxianwei$"));
        if (!xiaxianweiItem) {
            throw std::runtime_error("$variable$xiaxianwei is not found");
        }
        xiaxianwei = xiaxianweiItem->getValueAsInt();
        auto zuoxianweiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuoxianwei$"));
        if (!zuoxianweiItem) {
            throw std::runtime_error("$variable$zuoxianwei is not found");
        }
        zuoxianwei = zuoxianweiItem->getValueAsInt();
        auto youxianweiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youxianwei$"));
        if (!youxianweiItem) {
            throw std::runtime_error("$variable$youxianwei is not found");
        }
        youxianwei = youxianweiItem->getValueAsInt();
        auto tifeiyanshiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tifeiyanshi$"));
        if (!tifeiyanshiItem) {
            throw std::runtime_error("$variable$tifeiyanshi is not found");
        }
        tifeiyanshi = tifeiyanshiItem->getValueAsInt();
        auto tifeishuchuchixushijianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tifeishuchuchixushijian$"));
        if (!tifeishuchuchixushijianItem) {
            throw std::runtime_error("$variable$tifeishuchuchixushijian is not found");
        }
        tifeishuchuchixushijian = tifeishuchuchixushijianItem->getValueAsInt();
        auto xiangjichutujiangeItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangjichutujiange$"));
        if (!xiangjichutujiangeItem) {
            throw std::runtime_error("$variable$xiangjichutujiange is not found");
        }
        xiangjichutujiange = xiangjichutujiangeItem->getValueAsInt();
    }

    inline SetConfig::SetConfig(const SetConfig& obj)
    {
        zengyi = obj.zengyi;
        baoguang = obj.baoguang;
        xiangsudangliang = obj.xiangsudangliang;
        shangxianwei = obj.shangxianwei;
        xiaxianwei = obj.xiaxianwei;
        zuoxianwei = obj.zuoxianwei;
        youxianwei = obj.youxianwei;
        tifeiyanshi = obj.tifeiyanshi;
        tifeishuchuchixushijian = obj.tifeishuchuchixushijian;
        xiangjichutujiange = obj.xiangjichutujiange;
    }

    inline SetConfig& SetConfig::operator=(const SetConfig& obj)
    {
        if (this != &obj) {
            zengyi = obj.zengyi;
            baoguang = obj.baoguang;
            xiangsudangliang = obj.xiangsudangliang;
            shangxianwei = obj.shangxianwei;
            xiaxianwei = obj.xiaxianwei;
            zuoxianwei = obj.zuoxianwei;
            youxianwei = obj.youxianwei;
            tifeiyanshi = obj.tifeiyanshi;
            tifeishuchuchixushijian = obj.tifeishuchuchixushijian;
            xiangjichutujiange = obj.xiangjichutujiange;
        }
        return *this;
    }

    inline SetConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$SetConfig$");
        auto zengyiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zengyiItem->setName("$variable$zengyi$");
        zengyiItem->setValueFromInt(zengyi);
        assembly.addItem(zengyiItem);
        auto baoguangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        baoguangItem->setName("$variable$baoguang$");
        baoguangItem->setValueFromInt(baoguang);
        assembly.addItem(baoguangItem);
        auto xiangsudangliangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangsudangliangItem->setName("$variable$xiangsudangliang$");
        xiangsudangliangItem->setValueFromDouble(xiangsudangliang);
        assembly.addItem(xiangsudangliangItem);
        auto shangxianweiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shangxianweiItem->setName("$variable$shangxianwei$");
        shangxianweiItem->setValueFromInt(shangxianwei);
        assembly.addItem(shangxianweiItem);
        auto xiaxianweiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiaxianweiItem->setName("$variable$xiaxianwei$");
        xiaxianweiItem->setValueFromInt(xiaxianwei);
        assembly.addItem(xiaxianweiItem);
        auto zuoxianweiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zuoxianweiItem->setName("$variable$zuoxianwei$");
        zuoxianweiItem->setValueFromInt(zuoxianwei);
        assembly.addItem(zuoxianweiItem);
        auto youxianweiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        youxianweiItem->setName("$variable$youxianwei$");
        youxianweiItem->setValueFromInt(youxianwei);
        assembly.addItem(youxianweiItem);
        auto tifeiyanshiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tifeiyanshiItem->setName("$variable$tifeiyanshi$");
        tifeiyanshiItem->setValueFromInt(tifeiyanshi);
        assembly.addItem(tifeiyanshiItem);
        auto tifeishuchuchixushijianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tifeishuchuchixushijianItem->setName("$variable$tifeishuchuchixushijian$");
        tifeishuchuchixushijianItem->setValueFromInt(tifeishuchuchixushijian);
        assembly.addItem(tifeishuchuchixushijianItem);
        auto xiangjichutujiangeItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangjichutujiangeItem->setName("$variable$xiangjichutujiange$");
        xiangjichutujiangeItem->setValueFromInt(xiangjichutujiange);
        assembly.addItem(xiangjichutujiangeItem);
        return assembly;
    }

    inline bool SetConfig::operator==(const SetConfig& obj) const
    {
        return zengyi == obj.zengyi && baoguang == obj.baoguang && xiangsudangliang == obj.xiangsudangliang && shangxianwei == obj.shangxianwei && xiaxianwei == obj.xiaxianwei && zuoxianwei == obj.zuoxianwei && youxianwei == obj.youxianwei && tifeiyanshi == obj.tifeiyanshi && tifeishuchuchixushijian == obj.tifeishuchuchixushijian && xiangjichutujiange == obj.xiangjichutujiange;
    }

    inline bool SetConfig::operator!=(const SetConfig& obj) const
    {
        return !(*this == obj);
    }

}

