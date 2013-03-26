// main.cpp
//
// Main program

#include <QApplication>
#include "CamWidget.h"
#include "CameraStream.h"
#include "ui_main.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    QMainWindow *mainWindow = new QMainWindow;
    Ui_VisionSystemMainWindow ui;
    ui.setupUi(mainWindow);
	
    CamWidget camWidget;
    camWidget.setParent(ui.rawVideoContents);
    
    QSizePolicy camSizePolicy(QSizePolicy::MinimumExpanding , QSizePolicy::MinimumExpanding );
    camSizePolicy.setHorizontalStretch(0);
    camSizePolicy.setVerticalStretch(0);
    camSizePolicy.setHeightForWidth(camWidget.sizePolicy().hasHeightForWidth());
    camWidget.setSizePolicy(camSizePolicy);
    
    CameraStream stream;
    
    QObject::connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)), &camWidget, SLOT(setImage(const cv::Mat&)));

    mainWindow->show();
    return app.exec();
}
