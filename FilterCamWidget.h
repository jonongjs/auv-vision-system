// FilterCamWidget.h
//
// Widget for displaying a video feed with filter


#ifndef FILTERCAMWIDGET_H
#define FILTERCAMWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include "CamWidget.h"

class CameraStream;
class FilterCreator;
class ImageFilterBase;

class FilterCamWidget: public QWidget
{
    Q_OBJECT

public:
    FilterCamWidget(CameraStream *camstream);

	void setFilterList(QStringList filterList);
	void setCurrentFilter(int index);
	
public slots:
    void filterDidChange(int index);
	
private:
	CamWidget *camWidget;
    CameraStream *stream;

    FilterCreator *filterCreator;
    ImageFilterBase *filter;

	QVBoxLayout *filterLayout;
	QComboBox *filterComboBox;
	
	void filterFromName(QString filterName);
	void createLayout();

    //TODO: shift this out somewhere else
    std::vector<QWidget*> settingsList;
};

#endif//FILTERCAMWIDGET_H
