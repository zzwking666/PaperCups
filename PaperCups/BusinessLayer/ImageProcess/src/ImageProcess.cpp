#include "ImageProcess.hpp"
#include "rwul/imgqt/imgqt.hpp"

#include <QDebug>

#include "Modules.hpp"
#include "utility.hpp"


ImageProcess::ImageProcess(QObject* parent)
	: QThread(parent)
{

}

ImageProcess::~ImageProcess()
{
	stopThread();
}

void ImageProcess::startThread()
{
	if (_running)
	{
		return;
	}

	_running = true;
	start();
}

void ImageProcess::stopThread()
{
	if (!_running)
	{
		return;
	}

	{
		QMutexLocker locker(&_queueMutex);
		_running = false;
		_queueNotEmpty.wakeAll();
	}

	wait();
}

void ImageProcess::onFrameCaptured(rw::rqwc::MatInfo matInfo, size_t index)
{
	// 产量按相机出帧数统计,与帧是否被丢弃/判废无关
	++Modules::getInstance().asynchronousThreadModule.statisticalInfo.shengchanzongliang;

	QMutexLocker locker(&_queueMutex);

	// 队满丢最旧:实时场景下旧帧无意义,优先保证画面时效性
	if (_frameQueue.size() >= maxQueueSize)
	{
		_frameQueue.pop_front();
		++_dropCount;
	}

	_frameQueue.push_back(FramePacket{ std::move(matInfo), index });
	_queueNotEmpty.wakeOne();
}

void ImageProcess::run()
{
	buildDetEngine();

	while (_running)
	{
		FramePacket packet;
		{
			QMutexLocker locker(&_queueMutex);
			while (_frameQueue.empty() && _running)
			{
				_queueNotEmpty.wait(&_queueMutex);
			}

			if (!_running && _frameQueue.empty())
			{
				break;
			}

			packet = std::move(_frameQueue.front());
			_frameQueue.pop_front();
		}

		processFrame(packet);
	}

	destroyDetEngine();
}

void ImageProcess::buildDetEngine()
{
	try
	{
		rw::imev::DetEngineConfig config;
		config.modelPath = globalPath.modelPath.toStdString();
		config.conf_threshold = 0.1f;
		config.nms_threshold = 0.1f;
		detEngine_ = rw::imevt::DetEngineFactory::create(config, rw::imev::DetModelTypes::Yolov11_Detection_CudaAcc);
	}
	catch (const std::exception& e)
	{
		// 引擎创建失败(如模型文件缺失)时降级为透传显示,不影响程序运行
		qWarning() << "检测引擎创建失败,降级为透传显示:" << e.what();
		detEngine_.reset();
	}
}

void ImageProcess::destroyDetEngine()
{
	detEngine_.reset();
}

void ImageProcess::processFrame(FramePacket& packet)
{
	bool isDefective = false;

	// 引擎不可用时透传原始图像
	if (detEngine_)
	{
		ProcessResult result;
		result.cameraIndex = packet.index;
		result.detResult = detEngine_->processImg(packet.matInfo.mat);
		result.isDefective = judgeDefective(result.detResult);
		isDefective = result.isDefective;

		drawDetResult(packet.matInfo.mat, result.detResult);

		if (result.isDefective)
		{
			++Modules::getInstance().asynchronousThreadModule.statisticalInfo.feipinzongliang;
			emit defectDetected(result);
		}
	}

	QImage qimg = rw::img::cvMatToQImage(packet.matInfo.mat);
	emit imageReady(packet.index, qimg, isDefective);
}

void ImageProcess::drawDetResult(cv::Mat& mat, const rw::imev::DetResult& detResult)
{
	for (const auto& det : detResult)
	{
		const cv::Rect box(det.rect.leftTop.x, det.rect.leftTop.y,
			det.rect.width(), det.rect.height());

		cv::rectangle(mat, box, cv::Scalar(0, 0, 255), 2);
		cv::putText(mat, cv::format("%d %.2f", static_cast<int>(det.classId), det.conf),
			cv::Point(box.x, box.y - 5),
			cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 1);
	}
}

bool ImageProcess::judgeDefective(const rw::imev::DetResult& detResult) const
{
	// TODO: 按类别/面积/数量等条件完善判废规则
	return !detResult.empty();
}
