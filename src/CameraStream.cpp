// CameraStream.cpp
//
// Handles the camera stream

#include <QTimer>
#include <opencv2/highgui/highgui.hpp>
#include "CameraStream.h"

CameraStream::CameraStream(int cameraIndex)
{
    vidCapture = new cv::VideoCapture(cameraIndex);

    //TODO: use a thread instead?
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(retrieveFrame()));

    timer->start(42);
}

CameraStream::~CameraStream()
{
    delete vidCapture;
}

void CameraStream::retrieveFrame()
{
    // Just return if the capture device couldn't be opened
    if (!vidCapture->isOpened()) {
        return;
    }

    // Retrieve the image from the capture device
    (*vidCapture) >> currentFrame;

    emit imageUpdated(currentFrame);
}
