// FilterCreator.cpp
//
// Factory class for filters

#include <algorithm>
#include "FilterCreator.h"
// Headers for all the filters
#include "GaussianBlurFilter.h"
#include "GrayFilter.h"
#include "HSVFilter.h"

// Functions to create the filters
template<class T> ImageFilterBase* filterCreator() { return new T; }

FilterCreator::FilterCreator()
{
    filterMap["GaussianBlur"] = &filterCreator<GaussianBlurFilter>;
    filterMap["Gray"] = &filterCreator<GrayFilter>;
    filterMap["HSV"] =  &filterCreator<HSVFilter>;

    for (FilterMap::iterator it=filterMap.begin(); it!=filterMap.end(); ++it) {
        filterNames.push_back(it->first);
    }
    std::sort(filterNames.begin(), filterNames.end());
}

ImageFilterBase* FilterCreator::createFilter(const std::string& filterName)
{
    if (filterMap.find(filterName) != filterMap.end()) {
        return filterMap[filterName]();
    }
    return NULL;
}

const FilterCreator::StringList& FilterCreator::getFilterNames() const
{
    return filterNames;
}
