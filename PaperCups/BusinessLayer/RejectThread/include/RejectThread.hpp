#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <atomic>
#include <deque>

#include "ImageProcess.hpp"

// 剔废线程:阻塞等待 ImageProcess 判废结果,对废品执行剔除动作
class RejectThread : public QThread
{
	Q_OBJECT

public:
	explicit RejectThread(QObject* parent = nullptr);
	~RejectThread() override;

	// 生命周期,由 Modules::start()/stop() 驱动
	void startThread();
	void stopThread();

public slots:
	// 接收 ImageProcess 的判废结果,废品入队
	void onDefectDetected(const ProcessResult& result);

protected:
	void run() override;

private:
	// 剔废动作(气阀/运动控制等),当前为占位实现
	void executeReject(const ProcessResult& result);

private:
	static constexpr size_t maxQueueSize = 16;

	std::atomic<bool> _running{ false };
	QMutex _queueMutex;
	QWaitCondition _queueNotEmpty;
	std::deque<ProcessResult> _rejectQueue;
};
