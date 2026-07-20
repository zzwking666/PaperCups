#pragma once
#include <QString>

inline struct
{
	QString cameraIp1 = "1";
	QString cameraIp2 = "2";
	QString zMotionIp = "192.168.0.11";
}utility;

inline struct
{
public:
	QString projectHome = R"(D:\zfkjData\PaperCups\)";
public:
	QString configRootPath = projectHome + R"(config\)";
	QString modelRootPath = projectHome + R"(model\)";
	QString paperCupsConfigPath = configRootPath + R"(PaperCups.xml)";
	QString setConfigPath = configRootPath + R"(setConfig.xml)";
public:
	QString companyRootPath = projectHome + R"(txt\)";
	QString companyTxtPath = companyRootPath + R"(company.txt)";
	QString testImgRootPath = projectHome + R"(testImg\)";
}globalPath;