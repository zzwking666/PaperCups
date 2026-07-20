#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PaperCups.h"
#include <QTimer>
#include "rqw_LabelClickable.h"
#include "DlgCloseForm.h"
#include "ConfigModule.hpp"
#include "CameraModule.hpp"
#include "DlgProductSet.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PaperCupsClass; };
QT_END_NAMESPACE

class PaperCups : public QMainWindow
{
    Q_OBJECT

public:
    PaperCups(ConfigModule& configModule,CameraModule& cameraModule,QWidget* parent = nullptr);
    ~PaperCups();
public:
	void initializeComponents();
public:
	void build_ui();
	void build_connect();
	void build_PaperCupsData();
    void build_DlgCloseForm();
	void build_DlgProductSet();

public slots:
	void updateCameraLabelState(int cameraIndex, bool state);

	void onUpdateStatisticalInfoUI();

    void onCameraDisplay(size_t index, const QImage& image);

	void setConfigWindowClosed();

private slots:
	void pbtn_exit_clicked();
	void pbtn_set_clicked();
    void pbtn_resetProduct_clicked();

    void lb_title_clicked();
public:
	DlgProductSet* _dlgProductSet = nullptr;
private:
	rw::rqw::ClickableLabel* clickableTitle = nullptr;
	int minimizeCount{ 3 };
	DlgCloseForm* _dlgCloseForm = nullptr;
private:
    Ui::PaperCupsClass* ui;
    ConfigModule& _configModule;
	CameraModule& _cameraModule;
};

