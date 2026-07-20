#include "ImageStitch.hpp"
#include "rwul/imgqt/imgqt.hpp"

#include "Modules.hpp"


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
