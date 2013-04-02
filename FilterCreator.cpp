// FilterCreator.cpp
//
// Factory class for filters

#include "FilterCreator.h"
// Headers for all the filters
#include "GrayFilter.h"
#include "HSVFilter.h"

// Functions to create the filters
ImageFilterBase* grayFilterCreator() { return new GrayFilter; }
ImageFilterBase* hsvFilterCreator() { return new HSVFilter; }

FilterCreator::FilterCreator()
{
    filterMap["Gray"] = &grayFilterCreator; filterNames.push_back("Gray");
    filterMap["HSV"] =  &hsvFilterCreator;  filterNames.push_back("HSV");
}

ImageFilterBase* FilterCreator::createFilter(std::string filterName)
{
    if (filterMap.find(filterName) != filterMap.end()) {
        return filterMap[filterName]();
    }
    return NULL;
}

const std::vector<std::string>& FilterCreator::getFilterNames() const
{
    return filterNames;
}
