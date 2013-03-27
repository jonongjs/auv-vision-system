// main.cpp
//
// Main program

#include <QApplication>
#include "CamWidget.h"
#include "CameraStream.h"
#include "AuvMainWindow.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
	AuvMainWindow *mainWindow = new AuvMainWindow;
	
	//	Add raw camera stream
	CameraStream stream;
	QObject::connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)), mainWindow->getRawCamWidget(), SLOT(setImage(const cv::Mat&)));
	
    mainWindow->show();

    return app.exec();
}
