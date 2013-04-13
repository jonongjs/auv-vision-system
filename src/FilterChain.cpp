// FilterChain.cpp
//
// Class for a chain of filters

#include "FilterChain.h"
#include "FilterCreator.h"
#include "ImageFilterBase.h"
#include "CameraStream.h"
#include <algorithm>

FilterChain::FilterChain()
	: stream(0)
{
	filterCreator = new FilterCreator;
}

FilterChain::~FilterChain()
{
	delete filterCreator;

	for (Chain::iterator it=filterList.begin(); it!=filterList.end(); ++it) {
		delete (*it);
	}
}

ImageFilterBase* FilterChain::appendNewFilter()
{
	ImageFilterBase *filter = filterCreator->createFilter("GaussianBlur");
	filterList.push_back(filter);

	if (filterList.empty()) {
		if (stream) {
			connect(stream, SIGNAL(imageUpdated(const cv::Mat&)),
				filter, SLOT(setImage(const cv::Mat&)));
		}
	} else {
		connect(filterList.back(), SIGNAL(imageUpdated(const cv::Mat&)),
				filter, SLOT(setImage(const cv::Mat&)));
	}

	return filter;
}

void FilterChain::appendFilter(ImageFilterBase *filter)
{
	filterList.push_back(filter);
}

void FilterChain::removeFilter(ImageFilterBase *filter)
{
	//TODO: disconnect the filter
	Chain::iterator it = std::find(filterList.begin(), filterList.end(), filter);
	filterList.erase(it);
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
