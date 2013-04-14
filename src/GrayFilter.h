// GrayFilter.h
//
// Converts an image to grayscale

#ifndef GRAYFILTER_H
#define GRAYFILTER_H

#include "ImageFilterBase.h"

class GrayFilter : public ImageFilterBase
{
    Q_OBJECT

public:
    void setProperty(const std::string& /*propertyName*/, const std::string& /*value*/) { }
    std::string getProperty(const std::string& /*propertyName*/) { return ""; }

public slots:
    void setImage(const cv::Mat& image);

private:
    cv::Mat output;
};

#endif//GRAYFILTER_H	
