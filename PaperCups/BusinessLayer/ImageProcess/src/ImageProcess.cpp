#include "ImageProcess.hpp"
#include "rwul/imgqt/imgqt.hpp"

#include <QDebug>

#include <cmath>
#include <cstdio>
#include <map>

#include "Modules.hpp"
#include "utility.hpp"

// 类别ID -> 显示文字 映射表,按实际模型类别自行补充/修改
// 未在表中的 classId 将直接显示数字 ID
static const std::map<int, std::string> classIdNameMap = {
	{ 1, "身体" },
	{ 2, "缺陷" },
	// 在此继续添加,例如: { 3, "xxx" },
};

static std::string getClassName(int classId)
{
	const auto it = classIdNameMap.find(classId);
	return it != classIdNameMap.end() ? it->second : std::to_string(classId);
}


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

	QImage qimg = rw::img::cvMatToQImage(packet.matInfo.mat);

	// 引擎不可用时透传原始图像
	if (detEngine_)
	{
		ProcessResult result;
		result.cameraIndex = packet.index;
		result.detResult = detEngine_->processImg(packet.matInfo.mat);
		result.isDefective = judgeDefective(result.detResult);
		isDefective = result.isDefective;

		drawDetResult(qimg, result.detResult);

		if (result.isDefective)
		{
			++Modules::getInstance().asynchronousThreadModule.statisticalInfo.feipinzongliang;
			emit defectDetected(result);
		}
	}

	emit imageReady(packet.index, qimg, isDefective);
}

void ImageProcess::drawDetResult(QImage& image, const rw::imev::DetResult& detResult)
{
	for (const auto& det : detResult)
	{
		rw::ImagePainter::DrawRectangleConfig rectCfg;
		rectCfg.rect = det.rect;
		rectCfg.borderColor = rw::Color::Red;
		rectCfg.thickness = 5;
		rw::ImagePainter::drawRectangle(image, rectCfg);

		char text[64];
		// 置信度转为 [0,100] 整数分数显示
		std::snprintf(text, sizeof(text), "%s %d",
			getClassName(static_cast<int>(det.classId)).c_str(),
			static_cast<int>(std::lround(det.conf * 100.0f)));

		rw::ImagePainter::DrawTextConfig textCfg;
		textCfg.text = text;
		textCfg.color = rw::Color::Red;
		textCfg.fontSize = 10;
		// position 为文字左上角;框上方空间不足时改画到框内顶部,避免文字因整体在图外被跳过
		constexpr int textOffsetY = 30;
		const int textY = det.rect.leftTop.y >= textOffsetY
			? det.rect.leftTop.y - textOffsetY
			: det.rect.leftTop.y + 2;
		textCfg.position = rw::PointPixel(det.rect.leftTop.x, textY);
		rw::ImagePainter::drawText(image, textCfg);
	}
}

bool ImageProcess::judgeDefective(const rw::imev::DetResult& detResult) const
{
	// TODO: 按类别/面积/数量等条件完善判废规则
	return !detResult.empty();
}
