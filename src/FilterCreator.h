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
		typedef std::vector<std::string> StringList;
		FilterCreator();

		// Creates a filter based on its name.
		// NOTE: The caller must delete the returned pointer.
		ImageFilterBase* createFilter(const std::string& filterName);

		const StringList& getFilterNames() const;

	private:
		typedef ImageFilterBase* (*FilterCreationFunc)();
		typedef std::map<std::string, FilterCreationFunc> FilterMap;

		FilterMap filterMap;
		StringList filterNames;
};

#endif//FILTERCREATOR_H
