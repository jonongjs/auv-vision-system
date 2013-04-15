// GaussianBlurFilter.cpp
//
// Performs Gaussian blur on an image

#include <cstdlib>
#include <opencv2/imgproc/imgproc.hpp>
#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter()
    : sigma(1.5f), kernelSize(5,5)
{
    FilterProperty kernelSizeP("Kernel Size", INT_RANGE);
    kernelSizeP.intMin = 3;
    kernelSizeP.intStep = 2;
    filterProperties.push_back(kernelSizeP);

    FilterProperty sigmaP("Sigma", FLOAT_RANGE);
    filterProperties.push_back(sigmaP);

}

void GaussianBlurFilter::setProperty(const std::string& propertyName, const std::string& value)
{
    if (propertyName == "Kernel Size") {
        int size = atoi(value.c_str());
        kernelSize = cv::Size(size, size);
    } else if (propertyName == "Sigma") {
        sigma = atof(value.c_str());
    }
}

std::string GaussianBlurFilter::getProperty(const std::string& propertyName)
{
    std::ostringstream ss;
    if (propertyName == "Kernel Size") {
        ss << kernelSize.width;
    } else if (propertyName == "Sigma") {
        ss << sigma;
    }
    return ss.str();
}

void GaussianBlurFilter::setImage(const cv::Mat& image)
{
    cv::GaussianBlur(image, output, kernelSize, sigma);

    emit imageUpdated(output);
}
