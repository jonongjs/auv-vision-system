// FilterSettingWidget.h
//
// Widget for displaying settings of a filter


#ifndef FILTERSETTINGWIDGET_H
#define FILTERSETTINGWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ImageFilterBase.h"
#include "FilterChain.h"
#include "QListWidgetWithDrop.h"

class PropertyAdaptor;

class FilterSettingWidget: public QWidget
{
    Q_OBJECT

public:
	FilterSettingWidget(QWidget * parent = 0);
	FilterChain* chain;
	QListWidgetWithDrop *list;
	int index;

public slots:
	void filterChanged(int i);
	void filterChanged();

private:
	void createLayout();	

	QVBoxLayout *filterLayout;
	QList<QWidget*> settingWidgets;
	QList<PropertyAdaptor*> adaptors;
	ImageFilterBase *filter;
};

#endif
