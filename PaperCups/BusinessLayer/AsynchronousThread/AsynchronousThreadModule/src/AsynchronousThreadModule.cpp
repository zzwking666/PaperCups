#include "AsynchronousThreadModule.hpp"

bool AsynchronousThreadModule::build()
{
	refreshUIThread = std::make_unique<RefreshUIThread>(this);
	rejectThread = std::make_unique<RejectThread>(this);
	//zMotionPollingThread = std::make_unique<ZMotionPollingThread>(this);

	return true;
}

void AsynchronousThreadModule::destroy()
{
	/*if (zMotionPollingThread)
	{
		zMotionPollingThread.reset();
	}*/

	if (rejectThread)
	{
		rejectThread.reset();
	}

	if (refreshUIThread)
	{
		refreshUIThread.reset();
	}
}

void AsynchronousThreadModule::start()
{
	if (refreshUIThread)
	{
		refreshUIThread->startThread();
	}

	if (rejectThread)
	{
		rejectThread->startThread();
	}

	/*if (zMotionPollingThread)
	{
		zMotionPollingThread->startThread();
	}*/
}

void AsynchronousThreadModule::stop()
{
	/*if (zMotionPollingThread)
	{
		zMotionPollingThread->stopThread();
	}*/

	// 先停剔废线程,再停UI刷新线程
	if (rejectThread)
	{
		rejectThread->stopThread();
	}

	if (refreshUIThread)
	{
		refreshUIThread->stopThread();
	}
}
