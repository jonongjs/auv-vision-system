// FilterSettingWidget.cpp
//
// Widget for displaying settings of a filter


#include "FilterSettingWidget.h"
#include <cstdio>
#include <iostream>
#include <QLabel>
using namespace std;

FilterSettingWidget::FilterSettingWidget(){
	createLayout();
}

void FilterSettingWidget::createLayout(){
	filterLayout = new QVBoxLayout;
	this->setLayout(filterLayout);

	setStyleSheet("QWidget { background-color: #FFFFCC; }");

	QLabel *labelHeading=new QLabel("Settings");
	labelHeading->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
	filterLayout->addWidget(labelHeading);
}


void FilterSettingWidget::filterChanged(int index){
	printf("index %d\n",index);

 	//	Clear filter8 settings
 	foreach(QWidget *widget, settingWidgets)
		delete widget;
	settingWidgets.clear();

	//	Add new filter name
	if (index >= 0) {
	ImageFilterBase *filter = chain->getChain()[index];
	QLabel *label = new QLabel(QString::number(index+1)+" "+ QString::fromStdString(filter->name));
    filterLayout->addWidget(label, Qt::AlignCenter);
    settingWidgets.append(label);
	cout << filter->name << endl;
	
 	//	Add new filter properties
    const FilterProperties& properties =  filter->getFilterProperties();
    for (FilterProperties::const_iterator it=properties.begin(); it!=properties.end(); ++it) {
    	QLabel *label = new QLabel(QString::fromStdString(it->name));
    	filterLayout->addWidget(label, Qt::AlignCenter);
    	cout << it->name << " property" << endl;
        QWidget *tmp;
        switch (it->type) {
            case INT_RANGE:
                {
                    QSpinBox *spin = new QSpinBox(this);
                    tmp = spin;
                    spin->setMinimum(it->intMin);
                    spin->setMaximum(it->intMax);
                    spin->setSingleStep(it->intStep);
                }
                break;
            case FLOAT_RANGE:
                {
                    QDoubleSpinBox *spin = new QDoubleSpinBox(this);
                    tmp = spin;
                    spin->setMinimum(it->floatMin);
                    spin->setMaximum(it->floatMax);
                    spin->setSingleStep(it->floatStep);
                }
                break;
        }
        filterLayout->addWidget(tmp);
    }
	printf("done\n");
	}
}
	

