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
        int zengyi2{ 0 };
        int baoguang2{ 0 };
        double xiangsudangliang2{ 0 };
        int shangxianwei2{ 0 };
        int xiaxianwei2{ 0 };
        int zuoxianwei2{ 0 };
        int youxianwei2{ 0 };
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
        auto zengyi2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zengyi2$"));
        if (!zengyi2Item) {
            throw std::runtime_error("$variable$zengyi2 is not found");
        }
        zengyi2 = zengyi2Item->getValueAsInt();
        auto baoguang2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$baoguang2$"));
        if (!baoguang2Item) {
            throw std::runtime_error("$variable$baoguang2 is not found");
        }
        baoguang2 = baoguang2Item->getValueAsInt();
        auto xiangsudangliang2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangsudangliang2$"));
        if (!xiangsudangliang2Item) {
            throw std::runtime_error("$variable$xiangsudangliang2 is not found");
        }
        xiangsudangliang2 = xiangsudangliang2Item->getValueAsDouble();
        auto shangxianwei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shangxianwei2$"));
        if (!shangxianwei2Item) {
            throw std::runtime_error("$variable$shangxianwei2 is not found");
        }
        shangxianwei2 = shangxianwei2Item->getValueAsInt();
        auto xiaxianwei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiaxianwei2$"));
        if (!xiaxianwei2Item) {
            throw std::runtime_error("$variable$xiaxianwei2 is not found");
        }
        xiaxianwei2 = xiaxianwei2Item->getValueAsInt();
        auto zuoxianwei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuoxianwei2$"));
        if (!zuoxianwei2Item) {
            throw std::runtime_error("$variable$zuoxianwei2 is not found");
        }
        zuoxianwei2 = zuoxianwei2Item->getValueAsInt();
        auto youxianwei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youxianwei2$"));
        if (!youxianwei2Item) {
            throw std::runtime_error("$variable$youxianwei2 is not found");
        }
        youxianwei2 = youxianwei2Item->getValueAsInt();
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
        zengyi2 = obj.zengyi2;
        baoguang2 = obj.baoguang2;
        xiangsudangliang2 = obj.xiangsudangliang2;
        shangxianwei2 = obj.shangxianwei2;
        xiaxianwei2 = obj.xiaxianwei2;
        zuoxianwei2 = obj.zuoxianwei2;
        youxianwei2 = obj.youxianwei2;
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
            zengyi2 = obj.zengyi2;
            baoguang2 = obj.baoguang2;
            xiangsudangliang2 = obj.xiangsudangliang2;
            shangxianwei2 = obj.shangxianwei2;
            xiaxianwei2 = obj.xiaxianwei2;
            zuoxianwei2 = obj.zuoxianwei2;
            youxianwei2 = obj.youxianwei2;
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
        auto zengyi2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        zengyi2Item->setName("$variable$zengyi2$");
        zengyi2Item->setValueFromInt(zengyi2);
        assembly.addItem(zengyi2Item);
        auto baoguang2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        baoguang2Item->setName("$variable$baoguang2$");
        baoguang2Item->setValueFromInt(baoguang2);
        assembly.addItem(baoguang2Item);
        auto xiangsudangliang2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangsudangliang2Item->setName("$variable$xiangsudangliang2$");
        xiangsudangliang2Item->setValueFromDouble(xiangsudangliang2);
        assembly.addItem(xiangsudangliang2Item);
        auto shangxianwei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        shangxianwei2Item->setName("$variable$shangxianwei2$");
        shangxianwei2Item->setValueFromInt(shangxianwei2);
        assembly.addItem(shangxianwei2Item);
        auto xiaxianwei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        xiaxianwei2Item->setName("$variable$xiaxianwei2$");
        xiaxianwei2Item->setValueFromInt(xiaxianwei2);
        assembly.addItem(xiaxianwei2Item);
        auto zuoxianwei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        zuoxianwei2Item->setName("$variable$zuoxianwei2$");
        zuoxianwei2Item->setValueFromInt(zuoxianwei2);
        assembly.addItem(zuoxianwei2Item);
        auto youxianwei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        youxianwei2Item->setName("$variable$youxianwei2$");
        youxianwei2Item->setValueFromInt(youxianwei2);
        assembly.addItem(youxianwei2Item);
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
        return zengyi == obj.zengyi && baoguang == obj.baoguang && xiangsudangliang == obj.xiangsudangliang && shangxianwei == obj.shangxianwei && xiaxianwei == obj.xiaxianwei && zuoxianwei == obj.zuoxianwei && youxianwei == obj.youxianwei && zengyi2 == obj.zengyi2 && baoguang2 == obj.baoguang2 && xiangsudangliang2 == obj.xiangsudangliang2 && shangxianwei2 == obj.shangxianwei2 && xiaxianwei2 == obj.xiaxianwei2 && zuoxianwei2 == obj.zuoxianwei2 && youxianwei2 == obj.youxianwei2 && tifeiyanshi == obj.tifeiyanshi && tifeishuchuchixushijian == obj.tifeishuchuchixushijian && xiangjichutujiange == obj.xiangjichutujiange;
    }

    inline bool SetConfig::operator!=(const SetConfig& obj) const
    {
        return !(*this == obj);
    }

}

