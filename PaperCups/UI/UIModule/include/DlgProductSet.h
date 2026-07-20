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

	void btn_zengyi_clicked();
	void btn_baoguang_clicked();

public:
	Ui::DlgProductSetClass* ui;
private:
	ConfigModule& _configModule;
	CameraModule& _cameraModule;
};

