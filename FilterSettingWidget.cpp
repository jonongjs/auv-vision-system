// FilterSettingWidget.cpp
//
// Widget for displaying settings of a filter


#include "FilterSettingWidget.h"
#include <cstdio>
#include <QLabel>

FilterSettingWidget::FilterSettingWidget(){
	createLayout();
}

void FilterSettingWidget::createLayout(){
	filterLayout = new QVBoxLayout;
	this->setLayout(filterLayout);

	
	setStyleSheet("QWidget { background-color: brown; }");
	for (int i = 0; i < 100; i++){
		QLabel *label = new QLabel(QString::number(i)+" asd");
		filterLayout->addWidget(label);
	}
}


void FilterSettingWidget::filterChanged(int index){
	printf("%d filter changed\n",index);
	/*
	 if (filter) {
	 
	 	//	Clear filter settings
	 	QList<QWidget *> widgets = filterLayout->findChildren<QWidget *>();
	 	foreach(QWidget * widget, widgets)
   			delete widget;
		
		//	Add new filter name
		QLabel *label = new QLabel(QString::number(index+1)+" "+it->getName());
        filterLayout->addWidget(label, Qt::AlignCenter);
        	
		
		
	 	//	Add new filter properties
        const FilterProperties& properties = backend->filters[index]->getFilterProperties();
        for (FilterProperties::const_iterator it=properties.begin(); it!=properties.end(); ++it) {
        	QLabel *label = new QLabel(it->name);
        	filterLayout->addWidget(label, Qt::AlignCenter);
        
            QWidget *tmp;
            switch (it->type) {
                case INT_RANGE:
                    {
             l          QSpinBox *spin = new QSpinBox(this);
                        tmp = spin;
                        spin->setMinimum(it->intMin);
                        spin->setMaximum(it-ll>intMax);
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
	

