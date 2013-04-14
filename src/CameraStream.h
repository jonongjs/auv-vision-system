// CameraStream.h
//
// Handles the camera stream

#ifndef CAMERASTREAM_H
#define CAMERASTREAM_H

#include <QObject>
#include <opencv2/core/core.hpp>

namespace cv {
    class VideoCapture;
};
class QTimer;

class CameraStream : public QObject
{
    Q_OBJECT

public:
    CameraStream(int cameraIndex = 0);
    ~CameraStream();

    bool useVideo(const std::string& filename);
    bool useCamera(int cameraIndex = 0);

public slots:
    void retrieveFrame();

signals:
    void imageUpdated(const cv::Mat &updatedImage);

private:
    cv::VideoCapture *vidCapture;
    cv::Mat currentFrame;

    QTimer *timer;
};

#endif//CAMERASTREAM_H
