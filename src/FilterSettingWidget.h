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
	FilterSettingWidget(QWidget * parent = 0);
	FilterChain* chain;
	int index;

public slots:
	void filterChanged(int i);
	void filterChanged();

private:
	void createLayout();	
	QVBoxLayout *filterLayout;
	QList<QWidget*> settingWidgets;
};

#endif
