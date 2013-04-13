// HSVFilter.h
//
// Converts an image to HSV

#ifndef HSVFILTER_H
#define HSVFILTER_H

#include "ImageFilterBase.h"

class HSVFilter : public ImageFilterBase
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

#endif//HSVFILTER_H
