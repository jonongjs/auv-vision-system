// FilterSettingWidget.cpp
//
// Widget for displaying settings of a filter


#include "FilterSettingWidget.h"
#include <cstdio>
#include <iostream>
#include <QLabel>
using namespace std;

FilterSettingWidget::FilterSettingWidget(QWidget * parent): QWidget(parent) {
	createLayout();
}

void FilterSettingWidget::createLayout(){
	filterLayout = new QVBoxLayout;
	filterLayout->setAlignment(Qt::AlignTop);
	this->setLayout(filterLayout);

	setStyleSheet("QWidget { background-color:#F9F2F0;border-radius:10px;}");
}

void FilterSettingWidget::filterChanged(){
	if (index >= 0)
		filterChanged(index);
}

void FilterSettingWidget::filterChanged(int i){
	index = i;

 	//	Clear filter settings
 	foreach(QWidget *widget, settingWidgets)
		delete widget;
	settingWidgets.clear();
	
	//	Ensure size
	if ((int) chain->getChain().size() <= index)
		return;

	//	Add new filter name
	ImageFilterBase *filter = chain->getChain()[index];
	QLabel *label = new QLabel("Settings: "+QString::number(index+1)+" "+ QString::fromStdString(filter->name));
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
    filterLayout->addWidget(label);
    settingWidgets.append(label);

 	//	Add new filter properties
    const FilterProperties& properties =  filter->getFilterProperties();
    for (FilterProperties::const_iterator it=properties.begin(); it!=properties.end(); ++it) {
    	QLabel *label = new QLabel(QString::fromStdString(it->name));
    	filterLayout->addWidget(label);
		settingWidgets.append(label);

        QWidget *tmp;
        switch (it->type) {
            case INT_RANGE:
                {
                    QSpinBox *spin = new QSpinBox(this);
                    tmp = spin;
					//tmp->setStyleSheet("QSpinBox{margin-left:30px;}");
                    spin->setMinimum(it->intMin);
                    spin->setMaximum(it->intMax);
                    spin->setSingleStep(it->intStep);
                }
                break;
            case FLOAT_RANGE:
                {
                    QDoubleSpinBox *spin = new QDoubleSpinBox(this);
                    tmp = spin;
					//tmp->setStyleSheet("QDoubleSpinBox{margin-left:30px;}");
                    spin->setMinimum(it->floatMin);
                    spin->setMaximum(it->floatMax);
                    spin->setSingleStep(it->floatStep);
                }
                break;
        }

		tmp->setMinimumHeight(30);
        filterLayout->addWidget(tmp);
		settingWidgets.append(tmp);
    }
}
	

