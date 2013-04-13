// HSVFilter.cpp
//
// Converts an image to HSV

#include <opencv2/imgproc/imgproc.hpp>
#include "HSVFilter.h"

void HSVFilter::setImage(const cv::Mat& image)
{
    // Convert to grayscale
    cv::cvtColor(image, output, CV_BGR2HSV);

    emit imageUpdated(output);
}
