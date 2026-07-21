#pragma once

#include <QObject>
#include <QThread>

#include "rwul/rqwcd/rqwc_d.hpp"
#include "rwul/imevt/detection/imevt_det_factory.hpp"

class ImageStitch : public QThread
{
	Q_OBJECT

public:
	explicit ImageStitch(QObject *parent = nullptr);
	~ImageStitch() override;
public slots:
	// 相机回调函数
	void onFrameCaptured(rw::rqwc::MatInfo matInfo, size_t index);

signals:
	void imageReady(size_t index, const QImage& image);

private:
	std::unique_ptr<rw::imev::DetEngine> detEngine_ = nullptr;

	void buildDetEngine();
	void destroyDetEngine();
};
