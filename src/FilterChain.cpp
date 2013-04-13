// FilterChain.cpp
//
// Class for a chain of filters

#include "FilterChain.h"
#include "FilterCreator.h"
#include "ImageFilterBase.h"
#include "CameraStream.h"
#include <algorithm>

FilterChain::FilterChain(FilterCreator *creator)
	: stream(0), filterCreator(creator)
{
}

FilterChain::~FilterChain()
{
	for (Chain::iterator it=filterList.begin(); it!=filterList.end(); ++it) {
		delete (*it);
	}
}

ImageFilterBase* FilterChain::appendNewFilter()
{
	ImageFilterBase *filter = filterCreator->createFilter("GaussianBlur");
	appendFilter(filter);

	return filter;
}

void FilterChain::appendFilter(ImageFilterBase *filter)
{
	if (filterList.empty()) {
		if (stream) {
			connect(stream, SIGNAL(imageUpdated(const cv::Mat&)),
					filter, SLOT(setImage(const cv::Mat&)));
		}
	} else {
		connect(filterList.back(), SIGNAL(imageUpdated(const cv::Mat&)),
				filter, SLOT(setImage(const cv::Mat&)));
	}
	filterList.push_back(filter);
}

void FilterChain::removeFilter(ImageFilterBase *filter)
{
	Chain::iterator it = std::find(filterList.begin(), filterList.end(), filter);
	int index = it - filterList.begin(); 

	filterList.erase(it);
	delete filter;

	// Manage connections
	if (index < filterList.size()) {
		if (index == 0) {
			if (stream) {
				connect(stream, SIGNAL(imageUpdated(const cv::Mat&)),
						filterList[index], SLOT(setImage(const cv::Mat&)));
			}
		} else {
			connect(filterList[index-1], SIGNAL(imageUpdated(const cv::Mat&)),
					filterList[index], SLOT(setImage(const cv::Mat&)));
		}
		
		if (index < filterList.size()-1) {
			connect(filterList[index], SIGNAL(imageUpdated(const cv::Mat&)),
					filterList[index+1], SLOT(setImage(const cv::Mat&)));
		}
	}
}

const FilterChain::Chain& FilterChain::getChain()
{
	return filterList;
}

void FilterChain::setStream(CameraStream *str)
{
	if (!filterList.empty()) {
		if (stream) {
			disconnect(stream, SIGNAL(imageUpdated(const cv::Mat&)),
				filterList.front(), SLOT(setImage(const cv::Mat&)));
		}
		connect(str, SIGNAL(imageUpdated(const cv::Mat&)),
			filterList.front(), SLOT(setImage(const cv::Mat&)));
	}
	stream = str;
}

void FilterChain::changeFilterType(int index, const std::string& type)
{
	delete filterList[index];
	filterList[index] = filterCreator->createFilter(type);

	if (index == 0) {
		if (stream) {
			connect(stream, SIGNAL(imageUpdated(const cv::Mat&)),
				filterList[index], SLOT(setImage(const cv::Mat&)));
		}
	} else {
		connect(filterList[index-1], SIGNAL(imageUpdated(const cv::Mat&)),
			filterList[index], SLOT(setImage(const cv::Mat&)));
	}

	if (index != filterList.size()-1) {
		connect(filterList[index], SIGNAL(imageUpdated(const cv::Mat&)),
			filterList[index+1], SLOT(setImage(const cv::Mat&)));
	}
}
