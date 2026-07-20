#include "PaperCups.h"
#include "DlgProductSet.h"

#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <rwul/hoepZMotion/hoepZMotion_ZMotionDevice.hpp>
#include <rwul/rqwu/Keyboard/rqwu_NumberKeyboard.h>
#include "rwul/rqwu/rqwu_MessageBox.h"

#include "Modules.hpp"
#include "utility.hpp"

PaperCups::PaperCups(ConfigModule& configModule, CameraModule& cameraModule, QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::PaperCupsClass())
	, _configModule(configModule)
	, _cameraModule(cameraModule)
{
	ui->setupUi(this);

	initializeComponents();
}

PaperCups::~PaperCups()
{
	delete ui;
}

void PaperCups::initializeComponents()
{
	build_ui();

	build_connect();
}

void PaperCups::build_ui()
{
	build_PaperCupsData();
	build_DlgCloseForm();
	build_DlgProductSet();
}

void PaperCups::build_connect()
{
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked,
		this, &PaperCups::pbtn_exit_clicked);
	QObject::connect(ui->pbtn_set, &QPushButton::clicked,
		this, &PaperCups::pbtn_set_clicked);
	QObject::connect(ui->pbtn_resetProduct, &QPushButton::clicked,
		this, &PaperCups::pbtn_resetProduct_clicked);

	// 连接显示标题
	QObject::connect(clickableTitle, &rw::rqw::ClickableLabel::clicked,
		this, &PaperCups::lb_title_clicked);
}

void PaperCups::build_PaperCupsData()
{
	auto& paperCupsConfig = _configModule.paperCupsInfo;
	auto& setConfig = _configModule.setConfig;

	// 更新UI
	ui->lb_ProductCount->setText(QString::number(paperCupsConfig.shengchanzongliang));
	ui->lb_WasteCount->setText(QString::number(paperCupsConfig.feipinzongliang));
}

void PaperCups::build_DlgCloseForm()
{
	_dlgCloseForm = new DlgCloseForm(this);
}

void PaperCups::build_DlgProductSet()
{
	_dlgProductSet = new DlgProductSet(_configModule, _cameraModule, this);
}

void PaperCups::updateCameraLabelState(int cameraIndex, bool state)
{
	switch (cameraIndex)
	{
	case 1:
		if (state) {
			ui->label_camera1State->setText("连接成功");
			ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);font-size: 18px;font - weight: bold;padding: 5px 5px;} "));
		}
		else {
			ui->label_camera1State->setText("连接失败");
			ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);font-size: 18px;font - weight: bold;padding: 5px 5px;} "));
		}
		break;
	default:
		break;
	}
}

void PaperCups::onUpdateStatisticalInfoUI()
{
	auto& _statisticalInfo = Modules::getInstance().asynchronousThreadModule.statisticalInfo;

	ui->lb_ProductCount->setText(QString::number(_statisticalInfo.shengchanzongliang));
	ui->lb_WasteCount->setText(QString::number(_statisticalInfo.feipinzongliang));
}

void PaperCups::onCameraDisplay(size_t index, const QImage& image)
{
	
}

void PaperCups::setConfigWindowClosed()
{
	
}

void PaperCups::lb_title_clicked()
{
	if (0 != minimizeCount)
	{
		minimizeCount--;
	}
	else if (0 >= minimizeCount)
	{
		// 最小化主窗体
		this->showMinimized();
		minimizeCount = 3; // 重置最小化计数器
	}
}

void PaperCups::pbtn_exit_clicked()
{
#ifdef NDEBUG
	if (_dlgCloseForm)
	{
		_dlgCloseForm->exec();
	}
#else
	this->close();
#endif
}

void PaperCups::pbtn_set_clicked()
{
	_dlgProductSet->setFixedSize(this->width(), this->height());
	_dlgProductSet->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	_dlgProductSet->exec();
}

void PaperCups::pbtn_resetProduct_clicked()
{
	auto& _statisticalInfo = Modules::getInstance().asynchronousThreadModule.statisticalInfo;

	_statisticalInfo.shengchanzongliang = 0;
	_statisticalInfo.feipinzongliang = 0;
}