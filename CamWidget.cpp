// CamWidget.cpp
//
// Widget for displaying a video feed

#include <QPainter>
#include "CamWidget.h"
#include <opencv2/imgproc/imgproc.hpp>

CamWidget::CamWidget(QWidget *parent)
    : QWidget(parent)
{
    //setMinimumSize(0, 0);
    //setMaximumSize(1000, 680);
    //resize(320, 240);
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

    update();
}

// Events

void CamWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);
}

