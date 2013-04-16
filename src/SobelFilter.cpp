// SobelFilter.cpp
//
// Applies the Sobel filter on an image

#include <opencv2/imgproc/imgproc.hpp>
#include "SobelFilter.h"

SobelFilter::SobelFilter()
	: dx(1), dy(1)
{
}

void SobelFilter::setImage(const cv::Mat& image)
{
	// Convert to grayscale
	cv::Mat tmp;
	cvtColor(image, tmp, CV_BGR2GRAY);

	cv::Sobel(tmp, tmp, -1, dx, dy);

	cv::Mat channels[] = { tmp, tmp, tmp };
	cv::merge(channels, 3, output);

	emit imageUpdated(output);
}
