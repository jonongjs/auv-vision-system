// InvertFilter.h
//
// Inverts an image

#ifndef INVERTFILTER_H
#define INVERTFILTER_H

#include "ImageFilterBase.h"

class InvertFilter : public ImageFilterBase
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

#endif//INVERTFILTER_H

