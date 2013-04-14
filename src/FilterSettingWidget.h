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

class FilterSettingWidget: public QWidget
{
    Q_OBJECT

public:
	FilterSettingWidget();
	FilterChain* chain;

public slots:
	void filterChanged(int index);

private:
	void createLayout();	
	QVBoxLayout *filterLayout;
	QList<QWidget*> settingWidgets;
};

#endif
