// CamWidget.cpp
//
// Widget for displaying a video feed

#include <QPainter>
#include "CamWidget.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

CamWidget::CamWidget(QWidget *parent)
    : QWidget(parent)
{
}

// Slots
void CamWidget::setImage(const cv::Mat &updatedImage)
{
    // Perform conversion from cv::Mat to QImage
    cv::Mat tmpImage;
    cv::flip(updatedImage, tmpImage, 1); // Original image is inverted
	// Assume the image has 3 channels and is in BGR format
	cv::cvtColor(tmpImage, tmpImage, CV_BGR2RGB);
	QImage qImage(tmpImage.data, tmpImage.cols, tmpImage.rows, QImage::Format_RGB888);
	pixmap.convertFromImage(qImage);
    
    //std::cout << "Widget size: " << size().width() << " " << size().height() << std::endl;
    
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
//    float heightRatio = widgetSize.height() / (float)imageSize.height();

    return widthRatio;
}
