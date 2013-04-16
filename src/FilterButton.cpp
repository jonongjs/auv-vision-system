#include <QtGui>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include "FilterButton.h"
#include <iostream>
using namespace std;

FilterButton::FilterButton(const QString& name, const QStringList& options, const QString& currentOption, QWidget *parent)
	: QWidget(parent)
{
	deleteButton = createDeleteButton();

	filtersComboBox = createComboBox(options, currentOption);

	numberLabel = new QLabel(name);
	numberLabel->setStyleSheet("QLabel{color:black;height:20px;width:20px;background-color: #FFFFCC;padding:3px;}");

	//QVBoxLayout *rightLayout = new QVBoxLayout;
	//rightLayout->addWidget(deleteButton);
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(numberLabel);
	topLeftLayout->addWidget(filtersComboBox,1.3);
	topLeftLayout->addWidget(deleteButton,0.3);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(topLeftLayout);
	setLayout(mainLayout);

	connect(deleteButton,SIGNAL(clicked()),this,SLOT(buttonDelete()));		
}

void FilterButton::buttonDelete()
{
	emit deleteFilterButton(listItem);
}


QPushButton* FilterButton::createDeleteButton()
{
	deleteButton = new QPushButton;
	deleteButton->setText("X");
	deleteButton->setToolTip(tr("Remove This Filter"));
	deleteButton->setShortcut(tr("Del"));
	deleteButton->setStatusTip(tr("Remove This Filter"));
	deleteButton->setStyleSheet("QPushButton {color:white;border: 2px solid gray;border-radius: 6px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FF4D4D, stop: 1 #FFB8B8);min-width: 18px;}QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}QPushButton:flat {border: none;}QPushButton:default {border-color: navy;}");
	return deleteButton;
}


QComboBox* FilterButton::createComboBox(const QStringList& options, const QString& currentOption)
{
	filtersComboBox = new QComboBox;

	QListView * listView = new QListView(filtersComboBox);
	filtersComboBox->addItems(options);
	listView->setStyleSheet("QListView::item {     \
			margin:3px; }                                  \
			QListView::item:selected {                     \
			margin:3px;                                    \
			color: black;                                  \
			}                                              \
			");


	filtersComboBox->setView(listView);
	filtersComboBox->setStyleSheet(
					"QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 18px 1px 3px;min-width: 6em;}"
					"QComboBox:editable {background: white;}"
					"QComboBox:!editable, QComboBox::drop-down:editable {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFF, stop: 0.4 #FFFFFF,stop: 0.5 #FFFFFF, stop: 1.0 #FFFFFF);}"
					"QComboBox:on { padding-top: 3px;padding-left: 4px;}"
					"QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 15px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"
					"QComboBox::down-arrow {image: url(:/images/downarrow.png);}"
					"QComboBox::down-arrow:on { top: 2px;left: 1px;}");

	// Filter
	filtersComboBox->setCurrentIndex(options.indexOf(currentOption));

	// Connect the combobox's signal to our own
	connect(filtersComboBox, SIGNAL(currentIndexChanged(const QString&)),
			this, SIGNAL(selectionChanged(const QString&)));

	return filtersComboBox;
}

QString FilterButton::getName()
{
	return numberLabel->text();
}

void FilterButton::setName(const QString& text)
{
	return numberLabel->setText(text);
}
