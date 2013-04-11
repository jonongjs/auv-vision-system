// FilterCamWidget.cpp
//
// Widget for displaying a video feed with filter

#include "FilterCamWidget.h"
#include "FilterCreator.h"
#include "CameraStream.h"
#include "ImageFilterBase.h"
#include <iostream>

//HACK: temporary stuff
#include <QSpinBox>

using namespace std;

//TODO: This class shouldn't need to know about CameraStream
FilterCamWidget::FilterCamWidget(CameraStream *camstream)
    : stream(camstream), filter(NULL)
{
    //HACK: create a FilterCreator for now
    filterCreator = new FilterCreator;
    createLayout();

	camWidget = new CamWidget;
	filterLayout->addWidget(camWidget);
}


void FilterCamWidget::createLayout(){
	filterLayout = new QVBoxLayout;
	setLayout(filterLayout);
	setStyleSheet("QWidget { background-color: violet; }");
	filterComboBox = new QComboBox(this);
	filterComboBox->setMaximumHeight(40);
	filterLayout->addWidget(filterComboBox);
	connect(filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(filterDidChange(int)));
}


void FilterCamWidget::filterListChanged(QStringList filterList){
	setFilterList(filterList);
}


void FilterCamWidget::setFilterList(QStringList filterList){
	int index = filterComboBox->currentIndex();
	filterComboBox->clear();
	filterComboBox->addItems(filterList);
	if (index >= filterComboBox->count())
		index = filterComboBox->count() - 1;
	if (index == -1)
		index = 0;
	filterComboBox->setCurrentIndex(index);
}

void FilterCamWidget::filterDidChange(int index){
	setCurrentFilter(index);
}


void FilterCamWidget::setCurrentFilter(int index){
	if (index >= filterComboBox->count())
		return;
	cout << "Setting filter to index " << index << endl;
	
	filterFromName(filterComboBox->currentText());
	
	if (index != filterComboBox->currentIndex())
		filterComboBox->setCurrentIndex(index);
}


//HACK: helper function
void removeWindow(QWidget* widget)
{
    delete widget;
}

void FilterCamWidget::filterFromName(QString filterName){
    //TODO: filters should be handled by some other class; this class only
    //      should only be displaying filter outputs
    std::for_each(settingsList.begin(), settingsList.end(), removeWindow);
    settingsList.clear();

//    filterLayout->removeWidget(filter);
    delete filter;
    filter = filterCreator->createFilter(filterName.toStdString());
//    filterLayout->addWidget(filter);

    //HACK: create a settings window
    if (filter) {
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
            tmp->show();
            settingsList.push_back(tmp);
        }
        //ENDHACK

        QObject::connect(stream, SIGNAL(imageUpdated(const cv::Mat&)), filter, SLOT(setImage(const cv::Mat&)));
        QObject::connect(filter, SIGNAL(imageUpdated(const cv::Mat&)), camWidget, SLOT(setImage(const cv::Mat&)));
    }
}
