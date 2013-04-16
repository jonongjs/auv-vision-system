// SobelFilter.h
//
// Applies the Sobel filter on an image

#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "ImageFilterBase.h"

class SobelFilter : public ImageFilterBase
{
	Q_OBJECT

	public:
		SobelFilter();

		void setProperty(const std::string& /*propertyName*/, const std::string& /*value*/) { }
		std::string getProperty(const std::string& /*propertyName*/) { return ""; }

	public slots:
		void setImage(const cv::Mat& image);

	private:
		cv::Mat output;

		int dx, dy;
};

#endif//SOBELFILTER_H
