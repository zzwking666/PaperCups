#include "DlgProductSet.h"
#include "ui_DlgProductSet.h"

#include <QMessageBox>
#include "rwul/rqwu/Keyboard/rqwu_NumberKeyboard.h"
#include "Modules.hpp"

DlgProductSet::DlgProductSet(ConfigModule& configModule, CameraModule& cameraModule, QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgProductSetClass())
	, _configModule(configModule)
	, _cameraModule(cameraModule)
{
	ui->setupUi(this);

	build_ui();

	build_connect();
}

DlgProductSet::~DlgProductSet()
{
	delete ui;
}

void DlgProductSet::build_ui()
{
	read_config();
}

void DlgProductSet::read_config()
{
	auto& setConfig = _configModule.setConfig;

	ui->btn_zengyi->setText(QString::number(setConfig.zengyi));
	ui->btn_baoguang->setText(QString::number(setConfig.baoguang));
	ui->btn_xiangsudangliang->setText(QString::number(setConfig.xiangsudangliang));
}

void DlgProductSet::build_connect()
{
	QObject::connect(ui->btn_close, &QPushButton::clicked,
		this, &DlgProductSet::btn_close_clicked);

	QObject::connect(ui->btn_zengyi, &QPushButton::clicked,
		this, &DlgProductSet::btn_zengyi_clicked);
	QObject::connect(ui->btn_baoguang, &QPushButton::clicked,
		this, &DlgProductSet::btn_baoguang_clicked);
	QObject::connect(ui->btn_xiangsudangliang, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiangsudangliang_clicked);
}

void DlgProductSet::btn_close_clicked()
{
	emit paramsChanged();
	this->close();
}

void DlgProductSet::btn_xiangsudangliang_clicked()
{
	rw::rqwu::NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于等于0的数值");
			return;
		}
		auto& setConfig = _configModule.setConfig;
		ui->btn_xiangsudangliang->setText(value);
		setConfig.xiangsudangliang = value.toDouble();
	}
}

void DlgProductSet::btn_zengyi_clicked()
{
	rw::rqwu::NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于等于0的数值");
			return;
		}
		auto& setConfig = _configModule.setConfig;
		ui->btn_zengyi->setText(value);
		setConfig.zengyi = value.toDouble();
		_cameraModule.setCamera1Gain(setConfig.zengyi);
	}
}

void DlgProductSet::btn_baoguang_clicked()
{
	rw::rqwu::NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于等于0的数值");
			return;
		}
		auto& setConfig = _configModule.setConfig;
		ui->btn_baoguang->setText(value);
		setConfig.baoguang = value.toDouble();
		_cameraModule.setCamera1ExposureTime(setConfig.baoguang);
	}
}