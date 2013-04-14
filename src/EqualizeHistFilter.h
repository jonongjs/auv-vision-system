// EqualizeHistFilter.h
//
// Equalizes the histogram of an image

#ifndef EQUALIZEHISTFILTER_H
#define EQUALIZEHISTFILTER_H

#include "ImageFilterBase.h"

class EqualizeHistFilter : public ImageFilterBase
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

#endif//EQUALIZEHISTFILTER_H
