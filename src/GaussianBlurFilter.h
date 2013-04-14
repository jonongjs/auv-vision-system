// GaussianBlurFilter.h
//
// Performs Gaussian blur on an image

#ifndef GAUSSIANBLURFILTER_H
#define GAUSSIANBLURFILTER_H

#include "ImageFilterBase.h"

class GaussianBlurFilter : public ImageFilterBase
{
    Q_OBJECT

public:
    GaussianBlurFilter();
    void setProperty(const std::string& propertyName, const std::string& value);
    std::string getProperty(const std::string& propertyName);

public slots:
    void setImage(const cv::Mat& image);

private:
    float sigma;
    cv::Mat output;
    cv::Size kernelSize;
};

#endif//GAUSSIANBLURFILTER_H
