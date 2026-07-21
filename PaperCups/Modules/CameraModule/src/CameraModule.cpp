#include"CameraModule.hpp"
#include"Utility.hpp"
#include <QRegularExpression>

#ifdef BUILD_WITHOUT_HARDWARE
#include <QDir>
#endif

#include "Modules.hpp"

CameraModule::CameraModule()
{

}

CameraModule::~CameraModule()
{

}

bool CameraModule::build()
{
	if (!build_camera1())
	{
		qWarning("Camera 1 build failed");
	}
	return true;
}

void CameraModule::destroy()
{
	destroy_camera1();
}

void CameraModule::start()
{
#ifdef BUILD_WITHOUT_HARDWARE
	if (noHardwareTimer1)
	{
		noHardwareTimer1->start();
		onCameraStateChanged(1, true);
	}
	else
	{
		onCameraStateChanged(1, false);
	}
#else
	if (camera1)
	{
		camera1->startMonitor();
		onCameraStateChanged(1, true);
	}
	else
	{
		onCameraStateChanged(1, false);
	}
#endif
}

void CameraModule::stop()
{
#ifdef BUILD_WITHOUT_HARDWARE
	if (noHardwareTimer1)
	{
		noHardwareTimer1->stop();
	}
#else
	if (camera1)
	{
		camera1->stopMonitor();
		camera1->disconnectCamera();
	}
#endif
}

bool CameraModule::build_camera1()
{
#ifdef BUILD_WITHOUT_HARDWARE
	noHardwareTimer1 = new QTimer(this);
	noHardwareTimer1->setInterval(500);
	QObject::connect(noHardwareTimer1, &QTimer::timeout,
		this, &CameraModule::onNoHardwareCapture1);
	onCameraStateChanged(1, true);
	return true;
#else
	auto cameraList = rw::hoec::UtilityFunc<rw::hoec::CameraProvider::DVP>::getCameraInfoList();
	auto cameraMetaData1 = cameraMetaDataCheck(utility.cameraIp1, cameraList);

	if (cameraMetaData1.ip != "0")
	{
		try
		{
			camera1 = std::make_unique<rw::rqwc::DVPCameraPassive>();
			camera1->setIP(cameraMetaData1.ip);
			camera1->connectCamera();
			camera1->registerCallBackFunc();
			//camera1->startMonitor();
			setCamera1HardwareTrigger();

			auto cfg = Modules::getInstance().configModule.setConfig;

			camera1->setExposureTime(static_cast<size_t>(cfg.baoguang));
			camera1->setGain(static_cast<size_t>(cfg.zengyi));

			QObject::connect(camera1.get(), &rw::rqwc::DVPCameraPassive::callBackFuncPost,
				this, &CameraModule::onCamera1Capture);

			onCameraStateChanged(1, true);
			return true;
		}
		catch (const std::exception&)
		{
			onCameraStateChanged(1, false);
			return false;
		}
	}
	onCameraStateChanged(1, false);
	return false;
#endif
}

void CameraModule::destroy_camera1()
{
#ifdef BUILD_WITHOUT_HARDWARE
	if (noHardwareTimer1)
	{
		noHardwareTimer1->stop();
		delete noHardwareTimer1;
		noHardwareTimer1 = nullptr;
	}
	onCameraStateChanged(1, false);
#else
	if (camera1)
	{
		camera1.reset();
		onCameraStateChanged(1, false);
	}
#endif
}

void CameraModule::setCamera1TriggerOff()
{
	if (camera1)
	{
		camera1->setTriggerModeStatus(rw::hoec::TriggerModeStatus::OFF);
		isCamera1SoftTrigger = true;
	}
}

void CameraModule::setCamera1HardwareTrigger()
{
	if (camera1)
	{
		camera1->setTriggerModeStatus(rw::hoec::TriggerModeStatus::ON);
		//camera1->setTriggerSource(rw::hoec::TriggerSource::Line0);
		isCamera1SoftTrigger = false;
	}
}

void CameraModule::setCamera1ExposureTime(size_t exposureTime)
{
	if (camera1)
	{
		camera1->setExposureTime(exposureTime);
	}
}

void CameraModule::setCamera1Gain(size_t gain)
{
	if (camera1)
	{
		camera1->setGain(gain);
	}
}

void CameraModule::setCamera1Multiplier(size_t multiplier)
{
	if (camera1)
	{
		camera1->setMultiplier(multiplier);
	}
}

void CameraModule::setCamera1PostDivider(size_t postDivider)
{
	if (camera1)
	{
		camera1->setPostDivider(postDivider);
	}
}

void CameraModule::setCamera1LineHeight(unsigned int lineHeight)
{
	if (camera1)
	{
		camera1->setLineHeight(lineHeight);
	}
}

bool CameraModule::isTargetCamera(const QString& cameraIndex, const QString& targetName)
{
	QRegularExpression regex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
	QRegularExpressionMatch match = regex.match(targetName);

	if (match.hasMatch()) {
		auto matchString = match.captured(3);

		return cameraIndex == matchString;
	}

	return false;
}

rw::hoec::CameraInfo CameraModule::cameraMetaDataCheck(const QString& cameraIndex,
	const std::vector<rw::hoec::CameraInfo>& cameraInfo)
{
	for (const auto& cameraMetaData : cameraInfo) {
		if (isTargetCamera(cameraIndex, QString::fromStdString(cameraMetaData.ip))) {
			return cameraMetaData;
		}
	}
	rw::hoec::CameraInfo error;
	error.ip = "0";
	return error;
}

bool CameraModule::onBuildCamera(int index)
{
	if (index == 1)
	{
		return build_camera1();
	}
	return false;
}

void CameraModule::onDestroyCamera(int index)
{
	if (index == 1)
	{
		destroy_camera1();
	}
}

void CameraModule::onStartCamera(int index)
{
	if (index == 1 && camera1)
	{
		camera1->startMonitor();
	}
}

void CameraModule::onCamera1Capture(const rw::hoec::MatInfo& matInfo)
{
	emit onCameraCapture(matInfo, 1);
}

#ifdef BUILD_WITHOUT_HARDWARE
void CameraModule::onNoHardwareCapture1()
{
	// 首次触发时枚举目录下的图片
	if (noHardwareImages1.isEmpty())
	{
		const QDir dir(globalPath.testImgRootPath);
		noHardwareImages1 = dir.entryList(
			{ "*.jpg", "*.jpeg", "*.png", "*.bmp" }, QDir::Files, QDir::Name);
		noHardwareImageIndex1 = 0;
		if (noHardwareImages1.isEmpty())
		{
			qWarning("NoHardware: no image found in %s", qPrintable(globalPath.testImgRootPath));
			return;
		}
	}

	const QString imagePath = globalPath.testImgRootPath + noHardwareImages1.at(noHardwareImageIndex1);
	// 循环播放目录中的图片
	noHardwareImageIndex1 = (noHardwareImageIndex1 + 1) % noHardwareImages1.size();

	cv::Mat img = cv::imread(imagePath.toStdString());
	if (img.empty())
	{
		qWarning("NoHardware: camera1Img not found or empty");
		return;
	}

	rw::hoec::MatInfo matInfo;
	matInfo.mat = img;
	matInfo.frameInfo.frameNum = ++noHardwareFrameNum1;
	matInfo.frameInfo.width = img.cols;
	matInfo.frameInfo.height = img.rows;

	emit onCameraCapture(matInfo, 1);
}
#endif
