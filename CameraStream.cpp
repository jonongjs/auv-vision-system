// CameraStream.cpp
//
// Handles the camera stream

#include <QTimer>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
    cv::Mat frame;
    (*vidCapture) >> frame;

    // Perform conversion from cv::Mat to QImage
    cv::flip(frame, frame, 1); // Original image is inverted
    cv::cvtColor(frame, frame, CV_BGR2RGB); // Original is in BGR
    currentFrame = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);

    emit imageUpdated(&currentFrame);
}
