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

	//setStyleSheet("QWidget { background-color: #FFFFCC; }");

	for (int i = 0; i < 100; i++)
        {
		if(i==0)
		{
			QLabel *labelHeading=new QLabel("Settings");
			labelHeading->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
			filterLayout->addWidget(labelHeading);
		}
		QLabel *label = new QLabel(QString::number(i)+" asd");
		label->setStyleSheet("QLabel{color:black;font-size:14px;}");
		filterLayout->addWidget(label);
	}
}


void FilterSettingWidget::filterChanged(int index, FilterChain::Chain filters){
 	//	Clear filter settings
 	QList<QWidget *> widgets = filterLayout->findChildren<QWidget *>();
 	foreach(QWidget * widget, widgets)
		delete widget;
	
	//	Add new filter name
	ImageFilterBase *filter = filters[index];
	QLabel *label = new QLabel(QString::number(index+1)+" "+ QString::qstr(filter->name));
    filterLayout->addWidget(label, Qt::AlignCenter);
    	
	
	
 	//	Add new filter properties
    const FilterProperties& properties =  filter->getFilterProperties();
    for (FilterProperties::const_iterator it=properties.begin(); it!=properties.end(); ++it) {
    	QLabel *label = new QLabel(QString::fromStdString(it->name));
    	filterLayout->addWidget(label, Qt::AlignCenter);
    
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
}
	

