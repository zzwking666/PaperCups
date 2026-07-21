#include "AppRuntime.hpp"

#include "LicenseManager.hpp"
#include "DlgLicense.h"

#include <QDebug>
#include <QDialog>
#include <QMessageBox>

bool AppRuntime::initialize()
{
    if (!Modules::check())
    {
        return false;
    }

//#pragma region check license
//#ifndef BUILD_WITHOUT_HARDWARE
//	// 未授权时弹出 DlgLicense 引导激活；取消或激活失败则中止启动
//	if (!LicenseManager::verifyAtStartup())
//	{
//		DlgLicense dlg(LicenseManager::getMachineCode());
//		if (dlg.exec() != QDialog::Accepted)
//		{
//			return false;
//		}
//		if (!LicenseManager::applyActivationCode(dlg.activationCode()))
//		{
//			return false;
//		}
//		QMessageBox::information(nullptr, "提示",
//			QString("激活成功，%1").arg(LicenseManager::getAuthorizationExpiry()));
//	}
//#else
//	qDebug() << "[开发模式] 跳过授权校验";
//#endif
//#pragma endregion

	_modules.build();

	_paperCups = std::make_unique<PaperCups>(_modules.configModule, _modules.cameraModule);

	_modules.connect();

    build_connect();

    _modules.start();

    return true;
}

void AppRuntime::show()
{
#ifdef NDEBUG
    _paperCups->showFullScreen();
#else
    _paperCups->show();
#endif
}

void AppRuntime::shutdown()
{
	_modules.stop();
    _modules.destroy();
}

void AppRuntime::build_connect()
{
	// 连接相机模块的图像捕获信号到UI显示槽函数
    QObject::connect(&_modules.imageProcessModule, &ImageProcess::imageReady,
        _paperCups.get(), &PaperCups::onCameraDisplay);

	// 连接相机模块的状态变化信号到UI显示槽函数
    QObject::connect(&_modules.cameraModule, &CameraModule::onCameraStateChanged,
        _paperCups.get(), &PaperCups::updateCameraLabelState);

    // 连接异步线程刷新窗体UI
    QObject::connect(_modules.asynchronousThreadModule.refreshUIThread.get(), &RefreshUIThread::emit_RefreshUI,
		_paperCups.get(), &PaperCups::onUpdateStatisticalInfoUI);

    QObject::connect(_paperCups.get()->_dlgProductSet, &DlgProductSet::paramsChanged,
        _paperCups.get(), &PaperCups::setConfigWindowClosed);
}
