// Helper class to connect between property widget and the filter

#ifndef PROPERTYADAPTOR_H
#define PROPERTYADAPTOR_H

#include <QObject>
#include <string>
#include "ImageFilterBase.h"

class PropertyAdaptor : public QObject
{
	Q_OBJECT

	public:
		PropertyAdaptor(ImageFilterBase *_filter, const std::string& _property)
			: filter(_filter), property(_property)
		{ }

	public slots:
		void valueChanged(const QString& text) {
			filter->setProperty(property, text.toStdString());
		}

	private:
		ImageFilterBase *filter;
		std::string property;
};

#endif//PROPERTYADAPTOR_H
