// GrayFilter.cpp
//
// Converts an image to grayscale

#include <opencv2/imgproc/imgproc.hpp>
#include "GrayFilter.h"

void GrayFilter::setImage(const cv::Mat& image)
{
    // Convert to grayscale
    cv::cvtColor(image, output, CV_BGR2GRAY);

    emit imageUpdated(output);
}
