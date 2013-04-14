// InvertFilter.cpp
//
// Inverts an image

#include <opencv2/imgproc/imgproc.hpp>
#include "InvertFilter.h"

void InvertFilter::setImage(const cv::Mat& image)
{
    // Invert
    cv::convertScaleAbs(image, output, -1, 255);

    emit imageUpdated(output);
}

