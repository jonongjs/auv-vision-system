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

class FilterChain;

class FilterCamWidget: public QWidget
{
    Q_OBJECT

public:
    FilterCamWidget(FilterChain *);

	void setFilterList(QStringList& filterList);
	void setCurrentFilter(int index);

public slots:
    void filterDidChange(int index);
    void filterListChanged(QStringList& filterList);
	
private:
	CamWidget *camWidget;

	FilterChain *filterChain;

	QVBoxLayout *filterLayout;
	QComboBox *filterComboBox;
	
	void createLayout();

    //TODO: shift this out somewhere else
    std::vector<QWidget*> settingsList;
};

#endif//FILTERCAMWIDGET_H
