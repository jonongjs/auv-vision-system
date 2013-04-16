// FilterSettingWidget.cpp
//
// Widget for displaying settings of a filter

#include "FilterSettingWidget.h"
#include <iostream>
#include <QFile>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include "FilterButton.h"
#include "PropertyAdaptor.h"
using namespace std;

FilterSettingWidget::FilterSettingWidget(QWidget * parent): QWidget(parent)
{
	createLayout();

	QFile stylefile(":/qss/settingwidget.qss"); stylefile.open(QFile::ReadOnly);
	stylesheet = stylefile.readAll();
}

void FilterSettingWidget::createLayout()
{
	filterLayout = new QVBoxLayout;
	filterLayout->setAlignment(Qt::AlignTop);
	this->setLayout(filterLayout);

	setStyleSheet("QWidget { background-color:#F9F2F0;border-radius:10px;}");
}

void FilterSettingWidget::filterChanged()
{
	if (index >= 0)
		filterChanged(index);
}

void FilterSettingWidget::filterChanged(int _index)
{
	index = _index;

	// Clear filter settings
	foreach(QWidget *widget, settingWidgets)
		delete widget;
	settingWidgets.clear();

	foreach(PropertyAdaptor *adaptor, adaptors)
		delete adaptor;
	adaptors.clear();

	// Ensure size
	if ((int) chain->getChain().size() <= index)
		return;

	if (index >= 0) {
		// Add new filter name
		ImageFilterBase *filter = chain->getChain()[index];

		QString name = ((FilterButton*)list->itemWidget(list->item(index)))->getName();

		QLabel *label = new QLabel("Settings: "+name+") "+ QString::fromStdString(filter->name));
		label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;padding:3px;}");
		filterLayout->addWidget(label);
		settingWidgets.append(label);

		// Add new filter properties
		const FilterProperties& properties =  filter->getFilterProperties();

		if (properties.empty()){
			QLabel *label = new QLabel(tr("No settings available."));
			label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;padding:3px;}");
			filterLayout->addWidget(label);
			settingWidgets.append(label);
		}

		for (FilterProperties::const_iterator it=properties.begin(); it!=properties.end(); ++it) {
			QLabel *label = new QLabel(QString::fromStdString(it->name));
			label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");

			filterLayout->addWidget(label);
			settingWidgets.append(label);

			PropertyAdaptor *adaptor = new PropertyAdaptor(filter, it->name);
			adaptors.append(adaptor);

			QString curValue(QString::fromStdString(filter->getProperty(it->name)));

			// Create the property widget
			QWidget *tmp = createPropertyWidget(*it, curValue, adaptor);

			tmp->setStyleSheet(stylesheet);

			tmp->setMinimumHeight(30);
			filterLayout->addWidget(tmp);
			settingWidgets.append(tmp);
		}
	}
}

// Creates the property widgets
//NOTE: Add to the switch statement below if you need to add
//      new property types
QWidget* FilterSettingWidget::createPropertyWidget(
		const FilterProperty& p,
		const QString& curValue,
		PropertyAdaptor* adaptor)
{
	QWidget *tmp = 0;

	switch (p.type) {
		case INT_RANGE:
			{
				QSpinBox *spin = new QSpinBox(this);
				tmp = spin;
				spin->setMinimum(p.intMin);
				spin->setMaximum(p.intMax);
				spin->setSingleStep(p.intStep);
				spin->setValue(curValue.toInt());

				connect(spin, SIGNAL(valueChanged(const QString&)),
						adaptor, SLOT(valueChanged(const QString&)));
			}
			break;
		case FLOAT_RANGE:
			{
				QDoubleSpinBox *spin = new QDoubleSpinBox(this);
				tmp = spin;
				spin->setMinimum(p.floatMin);
				spin->setMaximum(p.floatMax);
				spin->setSingleStep(p.floatStep);
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
					QString::fromStdString(p.options)
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
	return tmp;
}
