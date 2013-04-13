// FilterChain.h
//
// Class for a chain of filters

#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

#include <QObject>
#include <vector>

class ImageFilterBase;

class FilterChain : public QObject
{
	Q_OBJECT

	public:
		typedef std::vector<ImageFilterBase*> Chain;

		FilterChain();
		~FilterChain();

		ImageFilterBase* appendNewFilter();
		void appendFilter(ImageFilterBase*);
		void removeFilter(ImageFilterBase*);

		const Chain& getChain();

		/*
	public slots:
		void listItemSwapped(int, int);
		void listItemAdded();
		void listItemDeleted();
		*/

	private:
		Chain filterList;
};

#endif//FILTERCHAIN_H
