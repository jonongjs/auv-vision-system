// FilterSettingWidget.cpp
//
// Widget for displaying settings of a filter


#include "FilterSettingWidget.h"
#include <cstdio>

FilterSettingWidget::FilterSettingWidget(){
	createLayout();
}

void FilterSettingWidget::createLayout(){
	filterLayout = new QVBoxLayout;
	setLayout(filterLayout);
	setStyleSheet("QWidget { background-color: brown; }");

}


void FilterSettingWidget::filterChanged(int index){
	printf("%d filter changed\n",index);
	/*
	 if (filter) {
	 
	 	//	Clear filter settings
	 	QList<QWidget *> widgets = filterLayout->findChildren<QWidget *>();
	 	foreach(QWidget * widget, widgets)
   			delete widget;
		
	 	//	Add new filter properties
        const FilterProperties& properties = filter->getFilterProperties();
        for (FilterProperties::const_iterator it=properties.begin(); it!=properties.end(); ++it) {
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
    }*/
}
	

