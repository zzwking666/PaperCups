#include "RejectThread.hpp"

#include <QDebug>


RejectThread::RejectThread(QObject* parent)
	: QThread(parent)
{

}

RejectThread::~RejectThread()
{
	stopThread();
}

void RejectThread::startThread()
{
	if (_running)
	{
		return;
	}

	_running = true;
	start();
}

void RejectThread::stopThread()
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

void RejectThread::onDefectDetected(const ProcessResult& result)
{
	QMutexLocker locker(&_queueMutex);

	if (_rejectQueue.size() >= maxQueueSize)
	{
		_rejectQueue.pop_front();
		qWarning() << "剔废队列已满,丢弃最旧的废品记录";
	}

	_rejectQueue.push_back(result);
	_queueNotEmpty.wakeOne();
}

void RejectThread::run()
{
	while (_running)
	{
		ProcessResult result;
		{
			QMutexLocker locker(&_queueMutex);
			while (_rejectQueue.empty() && _running)
			{
				_queueNotEmpty.wait(&_queueMutex);
			}

			if (!_running && _rejectQueue.empty())
			{
				break;
			}

			result = _rejectQueue.front();
			_rejectQueue.pop_front();
		}

		executeReject(result);
	}
}

void RejectThread::executeReject(const ProcessResult& result)
{
	// TODO: 接入剔废硬件动作(气阀/运动控制),需考虑废品到达剔废工位的延时
	
}
