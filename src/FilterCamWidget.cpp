// FilterCamWidget.cpp
//
// Widget for displaying a video feed with filter

#include "FilterCamWidget.h"
#include "FilterChain.h"
#include "FilterCreator.h"
#include "CameraStream.h"
#include "ImageFilterBase.h"
#include <iostream>

//HACK: temporary stuff
#include <QSpinBox>

using namespace std;

//TODO: This class shouldn't need to know about CameraStream
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
	filterComboBox->setStyleSheet("QComboBox{background-color:white;width:30px;height:25px;selection-background-color: lightgray;}");
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

void FilterCamWidget::filterDidChange(int index)
{
	setCurrentFilter(index);
}


void FilterCamWidget::setCurrentFilter(int index)
{
	if (index >= filterComboBox->count())
		return;
	cout << "Setting filter to index " << index << endl;

	const FilterChain::Chain& chain = filterChain->getChain();
	if (chain.empty()) {
		//TODO: Clear out the screen
	} else {
		if (index < chain.size()) {
			if (prevSelection >= 0 && prevSelection < chain.size()) {
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


//HACK: helper function
void removeWindow(QWidget* widget)
{
    delete widget;
}

/*
void FilterCamWidget::filterFromName(QString filterName)
{
    //TODO: filters should be handled by some other class; this class only
    //      should only be displaying filter outputs
    std::for_each(settingsList.begin(), settingsList.end(), removeWindow);
    settingsList.clear();

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

		QObject::connect(filter, SIGNAL(imageUpdated(const cv::Mat&)), camWidget, SLOT(setImage(const cv::Mat&)));
	}
}
*/
