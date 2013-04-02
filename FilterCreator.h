// FilterCreator.h
//
// Factory class for filters

#ifndef FILTERCREATOR_H
#define FILTERCREATOR_H

#include <map>
#include <string>
#include <vector>

class ImageFilterBase;

class FilterCreator
{
    public:
        FilterCreator();

        // Creates a filter based on its name.
        // NOTE: The caller must delete the returned pointer.
        ImageFilterBase* createFilter(const std::string& filterName);

        const std::vector<std::string>& getFilterNames() const;

    private:
        typedef ImageFilterBase* (*FilterCreationFunc)();
        typedef std::map<std::string, FilterCreationFunc> FilterMap;

        FilterMap filterMap;
        std::vector<std::string> filterNames;
};

#endif//FILTERCREATOR_H
