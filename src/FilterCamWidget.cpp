// FilterCamWidget.cpp
//
// Widget for displaying a video feed with filter

#include "FilterCamWidget.h"
#include "FilterChain.h"
#include "FilterCreator.h"
#include "ImageFilterBase.h"

using namespace std;

FilterCamWidget::FilterCamWidget(FilterChain *chain)
	: filterChain(chain), prevSelection(-1)
{
	createLayout();

	camWidget = new CamWidget;
	filterLayout->addWidget(camWidget);
}


void FilterCamWidget::createLayout()
{
	filterLayout = new QVBoxLayout;
	setLayout(filterLayout);
	setStyleSheet("QWidget { background-color: #E6E6E0;}");
	filterComboBox = new QComboBox(this);
	//filterComboBox->setMaximumHeight(40);
	//filterComboBox->setStyleSheet("QComboBox{background-color:white;width:30px;height:25px;selection-background-color: lightgray;}");
	filterComboBox->setStyleSheet(
			"QComboBox {color:black;border: 1px solid gray;border-radius: 3px;padding: 1px 18px 1px 3px;min-width: 6em;}"
			"QComboBox:editable {background: white;}"
			"QComboBox:!editable, QComboBox::drop-down:editable {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFF, stop: 0.4 #FFFFFF,stop: 0.5 #FFFFFF, stop: 1.0 #FFFFFF);}"
			"QComboBox:on { padding-top: 3px;padding-left: 4px;}"
			"QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 15px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"
			"QComboBox::down-arrow {image: url(:/images/downarrow.png);}"
			"QComboBox::down-arrow:on { top: 2px;left: 1px;}");

	filterLayout->addWidget(filterComboBox);
	connect(filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(filterDidChange(int)));
}


void FilterCamWidget::filterListChanged(QStringList& filterList)
{
	setFilterList(filterList);
}


void FilterCamWidget::setFilterList(QStringList& filterList)
{
	int index = filterComboBox->currentIndex();
	filterComboBox->clear();
	filterComboBox->addItems(filterList);

	if (index >= filterComboBox->count())
		index = filterComboBox->count() - 1;
	if (index == -1)
		index = 0;
	filterComboBox->setCurrentIndex(index);
}

// One of the filters changed types
void FilterCamWidget::filterTypeChanged(int index)
{
	if (index == filterComboBox->currentIndex()) {
		connect(filterChain->getChain()[index], SIGNAL(imageUpdated(const cv::Mat&)),
				camWidget, SLOT(setImage(const cv::Mat&)));
	}
}

// Selection index changed
void FilterCamWidget::filterDidChange(int index)
{
	setCurrentFilter(index);
}


void FilterCamWidget::setCurrentFilter(int index)
{
	if (index >= filterComboBox->count())
		return;

	const FilterChain::Chain& chain = filterChain->getChain();
	if (chain.empty()) {
		//TODO: Clear out the screen
	} else {
		if (index >= 0 && index < (int)chain.size()) {
			if (prevSelection >= 0 && prevSelection < (int)chain.size()) {
				disconnect(chain[prevSelection], SIGNAL(imageUpdated(const cv::Mat&)),
						camWidget, SLOT(setImage(const cv::Mat&)));
			}

			connect(chain[index], SIGNAL(imageUpdated(const cv::Mat&)),
					camWidget, SLOT(setImage(const cv::Mat&)));
		}
	}

	prevSelection = index;

	if (index != filterComboBox->currentIndex())
		filterComboBox->setCurrentIndex(index);
}
