// FilterCamWidget.cpp
//
// Widget for displaying a video feed with filter

#include "FilterCamWidget.h"
#include "FilterCreator.h"
#include "CameraStream.h"
#include "ImageFilterBase.h"
#include <iostream>

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


void FilterCamWidget::setFilterList(QStringList filterList){
	filterComboBox->clear();
	filterComboBox->addItems(filterList);
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



void FilterCamWidget::filterFromName(QString filterName){
    //TODO: filters should be handled by some other class; this class only
    //      should only be displaying filter outputs
    delete filter;
    filter = filterCreator->createFilter(filterName.toStdString());

    QObject::connect(stream, SIGNAL(imageUpdated(const cv::Mat&)), filter, SLOT(setImage(const cv::Mat&)));
	QObject::connect(filter, SIGNAL(imageUpdated(const cv::Mat&)), camWidget, SLOT(setImage(const cv::Mat&)));
}
