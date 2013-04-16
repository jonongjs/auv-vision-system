// CameraStream.h
//
// Handles the camera stream.
// Signals:
//   - imageUpdated(const Mat& updatedImage): updated image from the video feed

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
		// Triggered when an updated image is available
		void imageUpdated(const cv::Mat &updatedImage);

	private:
		cv::VideoCapture *vidCapture;
		cv::VideoWriter  *vidWriter;
		cv::Mat currentFrame;

		QTimer *timer;
		double fps;
		bool isVideo;
};

#endif//CAMERASTREAM_H
