// CamWidget.cpp
//
// Widget for displaying a video feed

#include <QPainter>
#include "CamWidget.h"

CamWidget::CamWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(300, 200);
    setMaximumSize(1000, 680);
    resize(320, 240);
}

// Slots
void CamWidget::setImage(QImage *updatedImage)
{
    pixmap.convertFromImage(*updatedImage);

    update();
}

// Events

void CamWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);
}

