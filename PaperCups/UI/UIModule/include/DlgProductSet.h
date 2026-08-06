#pragma once

#include <QDialog>
#include "ConfigModule.hpp"
#include "CameraModule.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class DlgProductSetClass; };
QT_END_NAMESPACE

class DlgProductSet : public QDialog
{
	Q_OBJECT

public:
	DlgProductSet(ConfigModule& configModule, CameraModule& cameraModule, QWidget* parent = nullptr);
	~DlgProductSet();

public:
	void build_ui();
	void read_config();
	void build_connect();

protected:
signals:
	void paramsChanged();

	void emit_changeLanguage(int index);
public slots:
private slots:
	void btn_close_clicked();

	void btn_xiangsudangliang_clicked();
	void btn_xiangsudangliang_2_clicked();

	void btn_zengyi_clicked();
	void btn_baoguang_clicked();
	void btn_zengyi_2_clicked();
	void btn_baoguang_2_clicked();

	void btn_shangxianwei_clicked();
	void btn_xiaxianwei_clicked();
	void btn_zuoxianwei_clicked();
	void btn_youxianwei_clicked();
	void btn_shangxianwei_2_clicked();
	void btn_xiaxianwei_2_clicked();
	void btn_zuoxianwei_2_clicked();
	void btn_youxianwei_2_clicked();

	void btn_tifeiyanshi_clicked();
	void btn_tifeishuchuchixushijian_clicked();
	void btn_xiangjichutujiange_clicked();

public:
	Ui::DlgProductSetClass* ui;
private:
	ConfigModule& _configModule;
	CameraModule& _cameraModule;
};

