// CamWidget.h
//
// Widget for displaying a video feed


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

private:
    QPixmap pixmap;
};

#endif//CAMWIDGET_H
