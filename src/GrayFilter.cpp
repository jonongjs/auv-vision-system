// GrayFilter.cpp
//
// Converts an image to grayscale

#include <opencv2/imgproc/imgproc.hpp>
#include "GrayFilter.h"

void GrayFilter::setImage(const cv::Mat& image)
{
    // Convert to grayscale
	cv::Mat tmp;
    cv::cvtColor(image, tmp, CV_BGR2GRAY);

	cv::Mat channels[] = { tmp, tmp, tmp};
	cv::merge(channels, 3, output);

    emit imageUpdated(output);
}
