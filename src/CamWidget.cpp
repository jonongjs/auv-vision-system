// CamWidget.cpp
//
// Widget for displaying a video feed

#include <QPainter>
#include "CamWidget.h"
#include <opencv2/imgproc/imgproc.hpp>

CamWidget::CamWidget(QWidget *parent)
	: QWidget(parent)
{
}

// Slots
void CamWidget::setImage(const cv::Mat &updatedImage)
{
	// Perform conversion from cv::Mat to QImage
	cv::Mat tmpImage;
	// Assume the image has 3 channels and is in BGR format
	cv::cvtColor(updatedImage, tmpImage, CV_BGR2RGB);
	QImage qImage(tmpImage.data, tmpImage.cols, tmpImage.rows, QImage::Format_RGB888);
	pixmap.convertFromImage(qImage);

	QSize newSize = calcZoom(pixmap.size()) * pixmap.size();
	pixmap = pixmap.scaled(newSize);

	resize(newSize);

	update();
}

// Events

void CamWidget::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);

	painter.drawPixmap(0, 0, pixmap);
}

// Helper functions

float CamWidget::calcZoom(const QSize &imageSize)
{
	QSize widgetSize = size();

	float widthRatio = widgetSize.width() / (float)imageSize.width();
    //float heightRatio = widgetSize.height() / (float)imageSize.height();

	return widthRatio;
}
