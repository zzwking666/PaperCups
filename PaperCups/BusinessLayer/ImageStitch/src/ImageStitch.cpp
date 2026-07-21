#include "ImageStitch.hpp"
#include "rwul/imgqt/imgqt.hpp"

#include "Modules.hpp"
#include "utility.hpp"


ImageStitch::ImageStitch(QObject* parent)
	: QThread(parent)
{

}

ImageStitch::~ImageStitch()
{

}

void ImageStitch::onFrameCaptured(rw::rqwc::MatInfo matInfo, size_t index)
{
	if (matInfo.mat.empty())
	{
		return;
	}

	// 不做任何处理，直接转发原始图像
	QImage qimg = rw::img::cvMatToQImage(matInfo.mat);
	emit imageReady(index, qimg);
}

void ImageStitch::buildDetEngine()
{
	rw::imev::DetEngineConfig config;
	config.modelPath = globalPath.modelPath.toStdString();
	config.conf_threshold = 0.1f;
	config.nms_threshold = 0.1f;
	detEngine_ = rw::imevt::DetEngineFactory::create(config, rw::imev::DetModelTypes::Yolov11_Detection_CudaAcc);
}

void ImageStitch::destroyDetEngine()
{
	detEngine_.reset();
}
