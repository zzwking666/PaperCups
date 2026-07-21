#pragma once

#include "IModule.hpp"
#include <QObject>
#include "RefreshUIThread.hpp"
#include "ZMotionPollingThread.hpp"
#include "RejectThread.hpp"

class AsynchronousThreadModule
	: public QObject, public IModule<bool>
{
	Q_OBJECT
public:
	bool build() override;
	void destroy() override;
	void start() override;
	void stop() override;
public:
	struct StatisticalInfo
	{
		std::atomic_uint64_t shengchanzongliang{ 0 };
		std::atomic_uint64_t feipinzongliang{ 0 };
	} statisticalInfo;
public:
	std::unique_ptr<RefreshUIThread> refreshUIThread{ nullptr };
	std::unique_ptr<RejectThread> rejectThread{ nullptr };
	//std::unique_ptr<ZMotionPollingThread> zMotionPollingThread{ nullptr };
};
