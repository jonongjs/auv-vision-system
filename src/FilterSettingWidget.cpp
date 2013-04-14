// FilterSettingWidget.cpp
//
// Widget for displaying settings of a filter

#include "FilterSettingWidget.h"
#include <iostream>
#include <QLabel>
#include <QComboBox>
#include "PropertyAdaptor.h"
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

	foreach(PropertyAdaptor *adaptor, adaptors)
		delete adaptor;
	adaptors.clear();
	
	//	Ensure size
	if ((int) chain->getChain().size() <= index)
		return;

	if (index >= 0) {
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

			PropertyAdaptor *adaptor = new PropertyAdaptor(filter, it->name);
			adaptors.append(adaptor);

			QString curValue(QString::fromStdString(filter->getProperty(it->name)));
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
						spin->setValue(curValue.toInt());

						connect(spin, SIGNAL(valueChanged(const QString&)),
								adaptor, SLOT(valueChanged(const QString&)));
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
						spin->setValue(curValue.toDouble());

						connect(spin, SIGNAL(valueChanged(const QString&)),
								adaptor, SLOT(valueChanged(const QString&)));
					}
					break;
				case STR_SELECTION:
					{
						QComboBox *combo = new QComboBox(this);
						tmp = combo;
						QStringList options =
							QString::fromStdString(it->options)
								.split("\n", QString::SkipEmptyParts);

						combo->addItems(options);

						int index = 0;
						foreach (QString option, options) {
							if (option == curValue) {
								combo->setCurrentIndex(index);
								break;
							}
							++index;
						}

						connect(combo, SIGNAL(currentIndexChanged(const QString&)),
								adaptor, SLOT(valueChanged(const QString&)));
					}
					break;
			}

			tmp->setMinimumHeight(30);
			filterLayout->addWidget(tmp);
			settingWidgets.append(tmp);
		}
	}
}

