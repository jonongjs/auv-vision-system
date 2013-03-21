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
    QObject::connect(&stream, SIGNAL(imageUpdated(QImage*)), &camwidget, SLOT(setImage(QImage*)));

    return app.exec();
}
