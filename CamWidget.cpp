// CamWidget.cpp
//
// Widget for displaying a video feed

#include <QPainter>
#include "CamWidget.h"
#include <opencv2/imgproc/imgproc.hpp>

CamWidget::CamWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(300, 200);
    setMaximumSize(1000, 680);
    resize(320, 240);
}

// Slots
void CamWidget::setImage(const cv::Mat &updatedImage)
{
    // Perform conversion from cv::Mat to QImage
    cv::Mat tmpImage;
    cv::flip(updatedImage, tmpImage, 1); // Original image is inverted
    cv::cvtColor(tmpImage, tmpImage, CV_BGR2RGB); // Original is in BGR
    QImage qImage(tmpImage.data, tmpImage.cols, tmpImage.rows, QImage::Format_RGB888);
    pixmap.convertFromImage(qImage);

    update();
}

// Events

void CamWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);
}

