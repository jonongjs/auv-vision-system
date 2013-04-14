// FilterCreator.cpp
//
// Factory class for filters

#include <algorithm>
#include "FilterCreator.h"
// Headers for all the filters
#include "ConvertColourFilter.h"
#include "GaussianBlurFilter.h"
#include "EqualizeHistFilter.h"
#include "InvertFilter.h"
#include "SobelFilter.h"

// Functions to create the filters
template<class T> ImageFilterBase* filterCreator() { return new T; }

FilterCreator::FilterCreator()
{
	// Build up a list of methods to create the filters
    filterMap["ConvertColour"] = &filterCreator<ConvertColourFilter>;
    filterMap["GaussianBlur"] = &filterCreator<GaussianBlurFilter>;
    filterMap["EqualizeHist"] =  &filterCreator<EqualizeHistFilter>;
    filterMap["Invert"]= &filterCreator<InvertFilter>;
    filterMap["Sobel"] = &filterCreator<SobelFilter>;

    for (FilterMap::iterator it=filterMap.begin(); it!=filterMap.end(); ++it) {
        filterNames.push_back(it->first);
    }
    std::sort(filterNames.begin(), filterNames.end());
}

// Creates filter when given its name, or NULL if not found
ImageFilterBase* FilterCreator::createFilter(const std::string& filterName)
{
    if (filterMap.find(filterName) != filterMap.end()) {
		ImageFilterBase* filter = filterMap[filterName]();
		filter->name = filterName;
		return filter;
    }
    return NULL;
}

// Returns the list of filter names available
const FilterCreator::StringList& FilterCreator::getFilterNames() const
{
    return filterNames;
}
