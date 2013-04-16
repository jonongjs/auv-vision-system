// FilterChain.h
//
// Class for a chain of filters

#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

#include <QObject>
#include <deque>
#include <string>

class CameraStream;
class FilterCreator;
class ImageFilterBase;

class FilterChain : public QObject
{
	Q_OBJECT

	public:
		typedef std::deque<ImageFilterBase*> Chain;

		FilterChain(FilterCreator *);
		~FilterChain();

		ImageFilterBase* appendNewFilter();
		ImageFilterBase* appendNewFilter(const std::string& type);
		void appendFilter(ImageFilterBase*);
		void removeFilter(ImageFilterBase*);
		void removeFilter(int index);
		void moveFilter(int fromIndex, int toIndex);

		void changeFilterType(int index, const std::string& type);

		const Chain& getChain();

		void setStream(CameraStream *str);

	private:
		Chain filterList;
		CameraStream  *stream;
		FilterCreator *filterCreator;
};

#endif//FILTERCHAIN_H
