#include "DlgProductSet.h"
#include "ui_DlgProductSet.h"

#include <QMessageBox>
#include <QPushButton>
#include "rwul/rqwu/Keyboard/rqwu_NumberKeyboard.h"
#include "Modules.hpp"

// 弹数字键盘编辑一个 int 参数:确认后校验非负,刷新按钮文字并写回配置
static bool editIntParam(QWidget* parent, QPushButton* btn, int& param)
{
	rw::rqwu::NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	if (numKeyBord.exec() != QDialog::Accepted)
	{
		return false;
	}

	const auto value = numKeyBord.getValue();
	if (value.toInt() < 0)
	{
		QMessageBox::warning(parent, "提示", "请输入大于等于0的数值");
		return false;
	}

	btn->setText(value);
	param = value.toInt();
	return true;
}

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

	ui->btn_shangxianwei->setText(QString::number(setConfig.shangxianwei));
	ui->btn_xiaxianwei->setText(QString::number(setConfig.xiaxianwei));
	ui->btn_zuoxianwei->setText(QString::number(setConfig.zuoxianwei));
	ui->btn_youxianwei->setText(QString::number(setConfig.youxianwei));

	ui->btn_zengyi_2->setText(QString::number(setConfig.zengyi2));
	ui->btn_baoguang_2->setText(QString::number(setConfig.baoguang2));
	ui->btn_xiangsudangliang_2->setText(QString::number(setConfig.xiangsudangliang2));

	ui->btn_shangxianwei_2->setText(QString::number(setConfig.shangxianwei2));
	ui->btn_xiaxianwei_2->setText(QString::number(setConfig.xiaxianwei2));
	ui->btn_zuoxianwei_2->setText(QString::number(setConfig.zuoxianwei2));
	ui->btn_youxianwei_2->setText(QString::number(setConfig.youxianwei2));

	ui->btn_tifeiyanshi->setText(QString::number(setConfig.tifeiyanshi));
	ui->btn_tifeishuchuchixushijian->setText(QString::number(setConfig.tifeishuchuchixushijian));
	ui->btn_xiangjichutujiange->setText(QString::number(setConfig.xiangjichutujiange));
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

	QObject::connect(ui->btn_shangxianwei, &QPushButton::clicked,
		this, &DlgProductSet::btn_shangxianwei_clicked);
	QObject::connect(ui->btn_xiaxianwei, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiaxianwei_clicked);
	QObject::connect(ui->btn_zuoxianwei, &QPushButton::clicked,
		this, &DlgProductSet::btn_zuoxianwei_clicked);
	QObject::connect(ui->btn_youxianwei, &QPushButton::clicked,
		this, &DlgProductSet::btn_youxianwei_clicked);

	QObject::connect(ui->btn_zengyi_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_zengyi_2_clicked);
	QObject::connect(ui->btn_baoguang_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_baoguang_2_clicked);
	QObject::connect(ui->btn_xiangsudangliang_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiangsudangliang_2_clicked);

	QObject::connect(ui->btn_shangxianwei_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_shangxianwei_2_clicked);
	QObject::connect(ui->btn_xiaxianwei_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiaxianwei_2_clicked);
	QObject::connect(ui->btn_zuoxianwei_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_zuoxianwei_2_clicked);
	QObject::connect(ui->btn_youxianwei_2, &QPushButton::clicked,
		this, &DlgProductSet::btn_youxianwei_2_clicked);

	QObject::connect(ui->btn_tifeiyanshi, &QPushButton::clicked,
		this, &DlgProductSet::btn_tifeiyanshi_clicked);
	QObject::connect(ui->btn_tifeishuchuchixushijian, &QPushButton::clicked,
		this, &DlgProductSet::btn_tifeishuchuchixushijian_clicked);
	QObject::connect(ui->btn_xiangjichutujiange, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiangjichutujiange_clicked);
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

void DlgProductSet::btn_xiangsudangliang_2_clicked()
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
		ui->btn_xiangsudangliang_2->setText(value);
		setConfig.xiangsudangliang2 = value.toDouble();
	}
}

void DlgProductSet::btn_zengyi_2_clicked()
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
		ui->btn_zengyi_2->setText(value);
		setConfig.zengyi2 = value.toDouble();
		_cameraModule.setCamera2Gain(setConfig.zengyi2);
	}
}

void DlgProductSet::btn_baoguang_2_clicked()
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
		ui->btn_baoguang_2->setText(value);
		setConfig.baoguang2 = value.toDouble();
		_cameraModule.setCamera2ExposureTime(setConfig.baoguang2);
	}
}

void DlgProductSet::btn_shangxianwei_clicked()
{
	editIntParam(this, ui->btn_shangxianwei, _configModule.setConfig.shangxianwei);
}

void DlgProductSet::btn_xiaxianwei_clicked()
{
	editIntParam(this, ui->btn_xiaxianwei, _configModule.setConfig.xiaxianwei);
}

void DlgProductSet::btn_zuoxianwei_clicked()
{
	editIntParam(this, ui->btn_zuoxianwei, _configModule.setConfig.zuoxianwei);
}

void DlgProductSet::btn_youxianwei_clicked()
{
	editIntParam(this, ui->btn_youxianwei, _configModule.setConfig.youxianwei);
}

void DlgProductSet::btn_shangxianwei_2_clicked()
{
	editIntParam(this, ui->btn_shangxianwei_2, _configModule.setConfig.shangxianwei2);
}

void DlgProductSet::btn_xiaxianwei_2_clicked()
{
	editIntParam(this, ui->btn_xiaxianwei_2, _configModule.setConfig.xiaxianwei2);
}

void DlgProductSet::btn_zuoxianwei_2_clicked()
{
	editIntParam(this, ui->btn_zuoxianwei_2, _configModule.setConfig.zuoxianwei2);
}

void DlgProductSet::btn_youxianwei_2_clicked()
{
	editIntParam(this, ui->btn_youxianwei_2, _configModule.setConfig.youxianwei2);
}

void DlgProductSet::btn_tifeiyanshi_clicked()
{
	editIntParam(this, ui->btn_tifeiyanshi, _configModule.setConfig.tifeiyanshi);
}

void DlgProductSet::btn_tifeishuchuchixushijian_clicked()
{
	editIntParam(this, ui->btn_tifeishuchuchixushijian, _configModule.setConfig.tifeishuchuchixushijian);
}

void DlgProductSet::btn_xiangjichutujiange_clicked()
{
	editIntParam(this, ui->btn_xiangjichutujiange, _configModule.setConfig.xiangjichutujiange);
}