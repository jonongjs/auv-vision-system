// GaussianBlurFilter.cpp
//
// Performs Gaussian blur on an image

#include <cstdlib>
#include <opencv2/imgproc/imgproc.hpp>
#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter()
    : sigma(1.5f), kernelSize(5,5)
{
}

void GaussianBlurFilter::setProperty(const std::string& propertyName, const std::string& value)
{
    if (propertyName == "kernelSize") {
        int size = atoi(value.c_str());
        kernelSize = cv::Size(size, size);
    } else if (propertyName == "sigma") {
        sigma = atof(value.c_str());
    }
}

std::string GaussianBlurFilter::getProperty(const std::string& propertyName)
{
    std::ostringstream ss;
    if (propertyName == "kernelSize") {
        ss << kernelSize.width;
    } else if (propertyName == "sigma") {
        ss << sigma;
    }
    return ss.str();
}

void GaussianBlurFilter::setImage(const cv::Mat& image)
{
    cv::GaussianBlur(image, output, kernelSize, sigma);

    emit imageUpdated(output);
}
