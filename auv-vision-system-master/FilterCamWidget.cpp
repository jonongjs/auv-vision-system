// FilterCamWidget.cpp
//
// Widget for displaying a video feed with filter

#include "FilterCamWidget.h"
#include "GrayFilter.h"
#include <iostream>
using namespace std;

FilterCamWidget::FilterCamWidget(CameraStream *stream)
{
	this->stream = stream;
    createLayout();
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
	
	filterLayout->removeWidget(filterBase);
	filterBase = filterFromName(filterComboBox->currentText());
	filterLayout->addWidget(filterBase);
	
	if (index != filterComboBox->currentIndex())
		filterComboBox->setCurrentIndex(index);
}



CamWidget* FilterCamWidget::filterFromName(QString filterName){
	CamWidget *camWidget = new CamWidget;
	QObject::connect(stream, SIGNAL(imageUpdated(const cv::Mat&)), camWidget, SLOT(setImage(const cv::Mat&)));
	return camWidget;	//	dummy stub
}
