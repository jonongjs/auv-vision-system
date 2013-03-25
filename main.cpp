// main.cpp
//
// Main program

#include <QApplication>
#include "CamWidget.h"
#include "CameraStream.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    CamWidget camwidget;
    camwidget.show();

    CameraStream stream;

    QObject::connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)), &camwidget, SLOT(setImage(const cv::Mat&)));

    return app.exec();
}
