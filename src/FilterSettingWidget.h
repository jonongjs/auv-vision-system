// FilterSettingWidget.h
//
// Widget for displaying settings of a filter
// Slots:
//   - filterChanged(): to notify the widget of a change in the currently selected filter
//   - filterChanged(int _index): to notify the widget of a change in the filter selection

#ifndef FILTERSETTINGWIDGET_H
#define FILTERSETTINGWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ImageFilterBase.h"
#include "FilterChain.h"
#include "QListWidgetWithDrop.h"

class FilterProperty;
class PropertyAdaptor;

class FilterSettingWidget: public QWidget
{
	Q_OBJECT

	public:
		FilterSettingWidget(QWidget * parent = 0);

		FilterChain *chain;
		QListWidgetWithDrop *list;

	public slots:
		void filterChanged(int _index);
		void filterChanged();

	private:
		void createLayout();
		QWidget* createPropertyWidget(
				const FilterProperty& p,
				const QString& curValue,
				PropertyAdaptor* adaptor);

		QVBoxLayout *filterLayout;
		QList<QWidget*> settingWidgets;
		QList<PropertyAdaptor*> adaptors;
		ImageFilterBase *filter;
		int index;

		QString stylesheet;
};

#endif
