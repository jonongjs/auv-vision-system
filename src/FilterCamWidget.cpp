// FilterCamWidget.cpp
//
// Widget for displaying a video feed with filter

#include "FilterCamWidget.h"
#include "FilterChain.h"
#include "FilterCreator.h"
#include "ImageFilterBase.h"
#include <QFile>

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
	// Stylesheet
	// Use the filterbutton qss
	QFile stylefile(":/qss/filterbutton.qss"); stylefile.open(QFile::ReadOnly);
	QString stylesheet(stylefile.readAll());

	filterLayout = new QVBoxLayout;
	setLayout(filterLayout);
	setStyleSheet("QWidget { background-color: #E6E6E0;}");
	filterComboBox = new QComboBox(this);
	//filterComboBox->setMaximumHeight(40);
	filterComboBox->setStyleSheet(stylesheet);

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
