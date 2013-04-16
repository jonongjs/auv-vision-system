// ImageFilterBase.h
//
// Base class that all filters must implement

#ifndef IMAGEFILTERBASE_H
#define IMAGEFILTERBASE_H

#include <QObject>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

enum FilterPropertyType { INT_RANGE, FLOAT_RANGE, STR_SELECTION };

struct FilterProperty
{
    std::string name;
    FilterPropertyType type;
    int intMin, intMax, intStep;
    float floatMin, floatMax, floatStep;
	std::string options; // Newline-separated options

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
    FilterProperties filterProperties;
};

#endif//IMAGEFILTERBASE_H
