#pragma once

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>

#include <atomic>
#include <deque>

#include "rwul/rqwcd/rqwc_d.hpp"
#include "rwul/imevt/detection/imevt_det_factory.hpp"

// 单帧处理结果:AI 检测结果 + 判废结论
struct ProcessResult
{
	size_t cameraIndex{ 0 };			// 相机序号(1=正面, 2=背面)
	rw::imev::DetResult detResult;		// 检测框集合
	bool isDefective{ false };			// 是否废品
};

Q_DECLARE_METATYPE(ProcessResult)

// 图像处理线程:接收相机帧,执行 AI 推理、画框显示、缺陷统计、剔废分发
class ImageProcess : public QThread
{
	Q_OBJECT

public:
	explicit ImageProcess(QObject *parent = nullptr);
	~ImageProcess() override;

	// 生命周期,由 Modules::start()/stop() 驱动
	void startThread();
	void stopThread();

public slots:
	// 相机回调:入队(有界,队满丢最旧)
	void onFrameCaptured(rw::rqwc::MatInfo matInfo, size_t index);

signals:
	void imageReady(size_t index, const QImage& image, bool isDefective);
	void defectDetected(const ProcessResult& result);

protected:
	void run() override;

private:
	struct FramePacket
	{
		rw::rqwc::MatInfo matInfo;
		size_t index{ 0 };
	};

	// 引擎的创建/销毁必须在 run() 内执行(TensorRT/CUDA 上下文线程亲和)
	void buildDetEngine();
	void destroyDetEngine();

	void processFrame(FramePacket& packet);
	void drawDetResult(cv::Mat& mat, const rw::imev::DetResult& detResult);

	// 判废规则接口:当前默认"检出任意框即废品",后续按类别/面积/数量扩展
	bool judgeDefective(const rw::imev::DetResult& detResult) const;

private:
	static constexpr size_t maxQueueSize = 4;

	std::atomic<bool> _running{ false };
	QMutex _queueMutex;
	QWaitCondition _queueNotEmpty;
	std::deque<FramePacket> _frameQueue;
	std::atomic_uint64_t _dropCount{ 0 };

	std::unique_ptr<rw::imev::DetEngine> detEngine_ = nullptr;
};
