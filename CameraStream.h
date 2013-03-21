// CameraStream.h
//
// Handles the camera stream

#ifndef CAMERASTREAM_H
#define CAMERASTREAM_H

#include <QObject>
#include <QImage>

namespace cv {
    class VideoCapture;
};

class CameraStream : public QObject
{
    Q_OBJECT

public:
    CameraStream(int cameraIndex=0);
    ~CameraStream();

public slots:
    void retrieveFrame();

signals:
    void imageUpdated(QImage *updatedImage);

private:
    cv::VideoCapture *vidCapture;
    QImage currentFrame;
};

#endif//CAMERASTREAM_H
