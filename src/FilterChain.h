// FilterChain.h
//
// Class for a chain of filters

#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

#include <QObject>
#include <deque>

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
		void appendFilter(ImageFilterBase*);
		void removeFilter(ImageFilterBase*);

		const Chain& getChain();

		void setStream(CameraStream *str);

		/*
	public slots:
		void listItemSwapped(int, int);
		void listItemAdded();
		void listItemDeleted();
		*/

	private:
		Chain filterList;
		CameraStream  *stream;
		FilterCreator *filterCreator;
};

#endif//FILTERCHAIN_H
