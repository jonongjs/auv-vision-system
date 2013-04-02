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
    cv::flip(updatedImage, tmpImage, 1); // Original image is inverted
    // If image only has a single channel, need to duplicate the channel
    if (updatedImage.channels() == 1) {
        cv::Mat channels[] = { tmpImage, tmpImage, tmpImage };
        cv::Mat tmpImage2;
        cv::merge(channels, 3, tmpImage2);
        QImage qImage(tmpImage2.data, tmpImage2.cols, tmpImage2.rows, QImage::Format_RGB888);
        pixmap.convertFromImage(qImage);
    } else {
        // Assume the image has 3 channels and is in BGR format
        cv::cvtColor(tmpImage, tmpImage, CV_BGR2RGB);
        QImage qImage(tmpImage.data, tmpImage.cols, tmpImage.rows, QImage::Format_RGB888);
        pixmap.convertFromImage(qImage);
    }

    pixmap = pixmap.scaled(calcZoom(pixmap.size())*pixmap.size());

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
    float heightRatio = widgetSize.height() / (float)imageSize.height();

    return std::min(widthRatio, heightRatio);
}
