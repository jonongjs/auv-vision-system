// ConvertColourFilter.cpp
//
// Converts an image to a different colour space

#include <cstdlib>
#include <utility>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include "ConvertColourFilter.h"

using namespace std;

ConvertColourFilter::ConvertColourFilter()
{
	typedef vector< pair<string, int> > MAPPING;
	MAPPING mappings;
	mappings.push_back(make_pair("BGR to Gray", (int)CV_BGR2GRAY));

	mappings.push_back(make_pair("BGR to HSV", (int)CV_BGR2HSV));
	mappings.push_back(make_pair("HSV to BGR", (int)CV_HSV2BGR));

	mappings.push_back(make_pair("BGR to HLS", (int)CV_BGR2HLS));
	mappings.push_back(make_pair("HLS to BGR", (int)CV_HLS2BGR));

	mappings.push_back(make_pair("BGR to XYZ", (int)CV_BGR2XYZ));
	mappings.push_back(make_pair("XYZ to BGR", (int)CV_XYZ2BGR));

	mappings.push_back(make_pair("BGR to YCrCb", (int)CV_BGR2YCrCb));
	mappings.push_back(make_pair("YCrCb to BGR", (int)CV_YCrCb2BGR));

	mappings.push_back(make_pair("BGR to CIE L*a*b*", (int)CV_BGR2Lab));
	mappings.push_back(make_pair("CIE L*a*b* to BGR", (int)CV_Lab2BGR));

	mappings.push_back(make_pair("BGR to CIE L*u*v*", (int)CV_BGR2Luv));
	mappings.push_back(make_pair("CIE L*u*v* to BGR", (int)CV_Luv2BGR));

	ostringstream ss;
	for (MAPPING::iterator it=mappings.begin(); it!=mappings.end(); ++it) {
		ss << it->first << '\n';
		conversionMap[it->first] = it->second;
	}
    FilterProperty conversionP("conversion", STR_SELECTION);
	conversionP.options = ss.str();

	filterProperties.push_back(conversionP);

	// Default value:
	conversionType = CV_BGR2GRAY;
}

void ConvertColourFilter::setProperty(const std::string& propertyName, const std::string& value)
{
    if (propertyName == "conversion") {
		conversionType = conversionMap[value];
    }
}

std::string ConvertColourFilter::getProperty(const std::string& propertyName)
{
    if (propertyName == "conversion") {
		for (map<string, int>::iterator it=conversionMap.begin(); it!=conversionMap.end(); ++it) {
			if (it->second == conversionType) {
				return it->first;
			}
		}
    }
    return "";
}

void ConvertColourFilter::setImage(const cv::Mat& image)
{
	cv::Mat tmp;
    cv::cvtColor(image, tmp, conversionType);

	if (tmp.channels() != 3) {
		cv::Mat channels[] = { tmp, tmp, tmp };
		cv::merge(channels, 3, output);
	} else {
		output = tmp;
	}

    emit imageUpdated(output);
}
