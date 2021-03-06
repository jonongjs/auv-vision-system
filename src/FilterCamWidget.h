// FilterCamWidget.h
//
// Widget for displaying a video feed with filter
// Slots:
//  - filterDidChange(int index): to register a change in viewing selection
//  - filterTypeChanged(int index): to register a change in filter type
//  - filterListChanged(QStringList& filterList): to register a change in the filter list


#ifndef FILTERCAMWIDGET_H
#define FILTERCAMWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include "CamWidget.h"

class FilterChain;

class FilterCamWidget: public QWidget
{
	Q_OBJECT

	public:
		FilterCamWidget(FilterChain *);

		void setFilterList(QStringList& filterList);
		void setCurrentFilter(int index);

		FilterChain *filterChain;

	public slots:
		void filterDidChange(int index);
		void filterTypeChanged(int index);
		void filterListChanged(QStringList& filterList);

	private:
		CamWidget *camWidget;

		QVBoxLayout *filterLayout;
		QComboBox *filterComboBox;

		int prevSelection;

		void createLayout();
};

#endif//FILTERCAMWIDGET_H
