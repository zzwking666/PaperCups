#pragma once

#include <QObject>
#include <QThread>

#include "rwul/rqwcd/rqwc_d.hpp"

class ImageStitch : public QThread
{
	Q_OBJECT

public:
	explicit ImageStitch(QObject *parent = nullptr);
	~ImageStitch() override;
public slots:
	// 相机回调函数
	void onFrameCaptured(rw::rqwc::MatInfo matInfo, size_t index);

private:
	// 计算丢帧用的变量
	int lastCam1FrameNum{ 0 };
	int lastCam2FrameNum{ 0 };

signals:
	void imageReady(size_t index, const QImage& image);
};
