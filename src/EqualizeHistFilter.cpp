// EqualizeHistFilter.h
//
// Equalizes the histogram of an image

#include <opencv2/imgproc/imgproc.hpp>
#include "EqualizeHistFilter.h"

void EqualizeHistFilter::setImage(const cv::Mat& image)
{
	// equalizeHist only works with a single channel
	cv::Mat tmp[3];
	cv::split(image, tmp);

	cv::equalizeHist(tmp[0], tmp[0]);
	cv::equalizeHist(tmp[1], tmp[1]);
	cv::equalizeHist(tmp[2], tmp[2]);

	cv::merge(tmp, 3, output);

	emit imageUpdated(output);
}
