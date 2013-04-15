// CameraStream.cpp
//
// Handles the camera stream

#include <QTimer>
#include <opencv2/highgui/highgui.hpp>
#include "CameraStream.h"

const int TIMEOUT = 42;

CameraStream::CameraStream(int cameraIndex)
    : vidWriter(0)
{
    vidCapture = new cv::VideoCapture(cameraIndex);
	isVideo = false;

    //TODO: use a thread instead?
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(retrieveFrame()));

    timer->start(TIMEOUT);
    fps = 1.0 / TIMEOUT;
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
    if (!vidCapture->read(currentFrame)) {
		if (isVideo) {
			// Rewind the video
			vidCapture->set(CV_CAP_PROP_POS_FRAMES, 0.0);
			vidCapture->read(currentFrame);
		}
	}

    // Write frame to file if we're recording
    if (vidWriter) {
        (*vidWriter) << currentFrame;
    }

    emit imageUpdated(currentFrame);
}

bool CameraStream::useVideo(const std::string& filename)
{
    vidCapture->release();

    bool success = vidCapture->open(filename);
    if (success) {
        //PROBLEM: OpenCV seems to read some framerates wrongly
        //double fps = vidCapture->get(CV_CAP_PROP_FPS) || 24.0;
        //int timeout = (int)(1000.0/fps);
        //HACK: seek to end to get time at end of video
        vidCapture->set(CV_CAP_PROP_POS_AVI_RATIO, 1.0);
        double totalTime = vidCapture->get(CV_CAP_PROP_POS_MSEC);
        double frameCount = vidCapture->get(CV_CAP_PROP_FRAME_COUNT);
        fps = totalTime / frameCount;
        int timeout = (int)fps;
        // Now rewind
        vidCapture->set(CV_CAP_PROP_POS_AVI_RATIO, 0.0);
        //END HACK
 
        timer->start(timeout);
		isVideo = true;
    } else {
		useCamera(0);
	}
    return success;
}

bool CameraStream::useCamera(int cameraIndex)
{
    vidCapture->release();
    timer->start(TIMEOUT);
    fps = 1.0 / TIMEOUT;
	isVideo = false;

    return vidCapture->open(cameraIndex);
}

bool CameraStream::writeImage(const std::string& filename)
{
    return cv::imwrite(filename, currentFrame);
}

void CameraStream::startRecording(const std::string& filename)
{
    vidWriter = new cv::VideoWriter(filename,
                            CV_FOURCC('M','J','P','G'),
                            fps,
                            currentFrame.size());
}

void CameraStream::stopRecording()
{
    delete vidWriter;
    vidWriter = 0;
}
