// FilterChain.cpp
//
// Class for a chain of filters

#include "FilterChain.h"
#include <algorithm>

FilterChain::FilterChain()
{
}

FilterChain::~FilterChain()
{
	//TODO: delete all the filters in the list?
}

ImageFilterBase* FilterChain::appendNewFilter()
{
	return 0;
}

void FilterChain::appendFilter(ImageFilterBase *filter)
{
	filterList.push_back(filter);
}

void FilterChain::removeFilter(ImageFilterBase *filter)
{
	Chain::iterator it = std::find(filterList.begin(), filterList.end(), filter);
	filterList.erase(it);
}

const FilterChain::Chain& FilterChain::getChain()
{
	return filterList;
}
