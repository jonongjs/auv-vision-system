// FilterChain.cpp
//
// Class for a chain of filters

#include "FilterChain.h"
#include "FilterCreator.h"
#include "ImageFilterBase.h"
#include "CameraStream.h"
#include <algorithm>

// Helper functions
template <class A, class B>
inline void connectStreams(A* strA, B* strB)
{
	QObject::connect(strA, SIGNAL(imageUpdated(const cv::Mat&)),
			strB, SLOT(setImage(const cv::Mat&)));
}

template <class A, class B>
inline void disconnectStreams(A* strA, B* strB)
{
	QObject::disconnect(strA, SIGNAL(imageUpdated(const cv::Mat&)), strB, SLOT(setImage(const cv::Mat&)));
}


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

// Add a new filter to the end of the chain
ImageFilterBase* FilterChain::appendNewFilter()
{
	std::string firstName = filterCreator->getFilterNames()[0]; //HACK: get the first filter name

	return appendNewFilter(firstName);
}

ImageFilterBase* FilterChain::appendNewFilter(const std::string& type)
{
	ImageFilterBase *filter = filterCreator->createFilter(type);
	appendFilter(filter);

	return filter;
}

void FilterChain::appendFilter(ImageFilterBase *filter)
{
	if (filterList.empty()) {
		if (stream) {
			connectStreams(stream, filter);
		}
	} else {
		connectStreams(filterList.back(), filter);
	}
	filterList.push_back(filter);
}

void FilterChain::removeFilter(ImageFilterBase *filter)
{
	Chain::iterator it = std::find(filterList.begin(), filterList.end(), filter);
	int index = it - filterList.begin(); 

	removeFilter(index);
}

void FilterChain::removeFilter(int index)
{
	ImageFilterBase *filter = filterList[index];

	filterList.erase(filterList.begin()+index);
	delete filter;

	// Manage connections
	if (index >= 0 && index < (int)filterList.size()) {
		if (index == 0) {
			if (stream) {
				connectStreams(stream, filterList[index]);
			}
		} else {
			connectStreams(filterList[index-1], filterList[index]);
		}

		if (index >= 0 && index < (int)filterList.size()-1) {
			connectStreams(filterList[index], filterList[index+1]);
		}
	}
}

const FilterChain::Chain& FilterChain::getChain()
{
	return filterList;
}

void FilterChain::setStream(CameraStream *str)
{
	// If the list is not empty, we connect the stream to the first filter
	if (!filterList.empty()) {
		if (stream) {
			disconnectStreams(stream, filterList.front());
		}
		connectStreams(str, filterList.front());
	}
	stream = str;
}

void FilterChain::changeFilterType(int index, const std::string& type)
{
	// Delete the filter...
	delete filterList[index];
	filterList[index] = filterCreator->createFilter(type);

	// ...then fix back the connections for the new filter
	if (index == 0) {
		if (stream) {
			connectStreams(stream, filterList[index]);
		}
	} else {
		connectStreams(filterList[index-1], filterList[index]);
	}

	if (index != (int)filterList.size()-1) {
		connectStreams(filterList[index], filterList[index+1]);
	}
}

void FilterChain::moveFilter(int fromIndex, int toIndex)
{
	ImageFilterBase *filter = filterList[fromIndex];
	int lastIndex = filterList.size() - 1;

	// Disconnect first
	if (fromIndex == 0) {
		if (stream) {
			disconnectStreams(stream, filter);
		}
	} else {
		disconnectStreams(filterList[fromIndex-1], filter);
	}
	if (fromIndex < lastIndex) {
		disconnectStreams(filter, filterList[fromIndex+1]);
	}

	if (toIndex == 0) {
		if (stream) {
			disconnectStreams(stream, filterList[toIndex]);
		}
	} else {
		disconnectStreams(filterList[toIndex-1], filterList[toIndex]);
	}
	if (toIndex < lastIndex) {
		disconnectStreams(filterList[toIndex], filterList[toIndex+1]);
	}
	// End of disconnections

	// Rearrange
	filterList.erase(filterList.begin()+fromIndex);
	filterList.insert(filterList.begin()+toIndex, filter);

	// Reconections
	if (fromIndex == 0) {
		if (stream) {
			connectStreams(stream, filterList[fromIndex]);
		}
	} else {
		connectStreams(filterList[fromIndex-1], filterList[fromIndex]);
	}
	if (fromIndex < lastIndex) {
		connectStreams(filterList[fromIndex], filterList[fromIndex+1]);
	}

	if (toIndex == 0) {
		if (stream) {
			connectStreams(stream, filter);
		}
	} else {
		connectStreams(filterList[toIndex-1], filter);
	}
	if (toIndex < lastIndex) {
		connectStreams(filter, filterList[toIndex+1]);
	}
}
