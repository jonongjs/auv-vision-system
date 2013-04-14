// CameraStream.h
//
// Handles the camera stream

#ifndef CAMERASTREAM_H
#define CAMERASTREAM_H

#include <QObject>
#include <opencv2/core/core.hpp>

namespace cv {
    class VideoCapture;
    class VideoWriter;
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

	bool writeImage(const std::string& filename);
	void startRecording(const std::string& filename);
	void stopRecording();

public slots:
    void retrieveFrame();

signals:
    void imageUpdated(const cv::Mat &updatedImage);

private:
    cv::VideoCapture *vidCapture;
    cv::VideoWriter  *vidWriter;
    cv::Mat currentFrame;

    QTimer *timer;
	double fps;
};

#endif//CAMERASTREAM_H
