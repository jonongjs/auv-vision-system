// ConvertColourFilter.h
//
// Converts an image to a different colour space

#ifndef CONVERTCOLOURFILTER_H
#define CONVERTCOLOURFILTER_H

#include "ImageFilterBase.h"
#include <map>

class ConvertColourFilter : public ImageFilterBase
{
	Q_OBJECT

	public:
		ConvertColourFilter();

		void setProperty(const std::string& /*propertyName*/, const std::string& /*value*/);
		std::string getProperty(const std::string& /*propertyName*/);

	public slots:
		void setImage(const cv::Mat& image);

	private:
		cv::Mat output;
		int conversionType;
		std::map<std::string, int> conversionMap;
};

#endif//CONVERTCOLOURFILTER_H	
