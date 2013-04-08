// ImageFilterBase.h
//
// Base class that all filters must implement

#ifndef IMAGEFILTERBASE_H
#define IMAGEFILTERBASE_H

#include <QObject>
#include <string>
#include <opencv2/core/core.hpp>

class ImageFilterBase : public QObject
{
    Q_OBJECT

public:
    virtual void setProperty(const std::string& propertyName, const std::string& value) = 0;
    virtual std::string getProperty(const std::string& propertyName) = 0;

public slots:
    virtual void setImage(const cv::Mat& image) = 0;

signals:
    void imageUpdated(const cv::Mat& image);
};

#endif//IMAGEFILTERBASE_H
