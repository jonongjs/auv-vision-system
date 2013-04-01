// FilterCamWidget.h
//
// Widget for displaying a video feed with filter


#ifndef FILTERCAMWIDGET_H
#define FILTERCAMWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include "ImageFilterBase.h"
#include "CamWidget.h"
#include "CameraStream.h"

class FilterCamWidget: public QWidget
{
    Q_OBJECT

public:
    FilterCamWidget(CameraStream *stream);
	void setFilterList(QStringList filterList);
	void setCurrentFilter(int index);
	CamWidget* filterBase;
	
public slots:
    void filterDidChange(int index);
	
private:
	QVBoxLayout *filterLayout;
	QComboBox *filterComboBox;
	
	CameraStream *stream;
	
	CamWidget* filterFromName(QString filterName);
	void createLayout();
};

#endif
    
