// CamWidget.h
//
// Widget for displaying a video feed
// Slots:
//   - setImage(const Mat& updatedImage): set this to update the image

#ifndef CAMWIDGET_H
#define CAMWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>

class CamWidget: public QWidget
{
	Q_OBJECT

	public:
		CamWidget(QWidget *parent = 0);

	public slots:
		void setImage(const cv::Mat &updatedImage);

	protected:
		void paintEvent(QPaintEvent *event);

		float calcZoom(const QSize &imageSize);

	private:
		QPixmap pixmap;
};

#endif//CAMWIDGET_H
