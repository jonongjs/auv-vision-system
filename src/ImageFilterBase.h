// ImageFilterBase.h
//
// Base class that all filters must implement
//
// ImageFilterBase
// Slots:
//   - setImage(const Mat& image): set this to update the image
// Signals:
//   - imageUpdated(const Mat& image): triggered once an image is updated
//
// FilterProperty
// Class representing the properties of a filter

#ifndef IMAGEFILTERBASE_H
#define IMAGEFILTERBASE_H

#include <QObject>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

enum FilterPropertyType {
	INT_RANGE,    // Integer range (intMin, intMax, intStep represent the
	              //   minimum, maximum and step in spinboxes respectively).
	FLOAT_RANGE,  // Float range (floatMin, floatMax, floatStep represent the
	              //   minimum, maximum and step in spinboxes respectively).
	STR_SELECTION // Selection of strings (combobox of string options).
};

struct FilterProperty
{
	std::string name; // Name of the property
	FilterPropertyType type; // Type of the property
	int intMin, intMax, intStep; // Used by INT_RANGE
	float floatMin, floatMax, floatStep; // Used by FLOAT_RANGE
	std::string options; // Used by STR_SELECTION; newline-separated options

	FilterProperty(const std::string& propertyName, FilterPropertyType _type)
		: name(propertyName), type(_type),
		intMin(INT_MIN), intMax(INT_MAX), intStep(1),
		floatMin(FLT_MIN), floatMax(FLT_MAX), floatStep(0.01)
	{ }
};
typedef std::vector<FilterProperty> FilterProperties;


class ImageFilterBase : public QObject
{
	Q_OBJECT

	public:
		virtual void setProperty(const std::string& propertyName, const std::string& value) = 0;
		virtual std::string getProperty(const std::string& propertyName) = 0;

		virtual const FilterProperties& getFilterProperties() { return filterProperties; };

		std::string name;

	public slots:
		virtual void setImage(const cv::Mat& image) = 0;

	signals:
		void imageUpdated(const cv::Mat& image);

	protected:
		// Implementing classes should fill this list up with FilterProperty(s) (if any)
		FilterProperties filterProperties;
};

#endif//IMAGEFILTERBASE_H
