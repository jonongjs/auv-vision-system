// FilterButton.cpp
//
// Button representing a filter in the list of filters

#include <QComboBox>
#include <QFile>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
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
	// Stylesheet
	QFile stylefile(":/qss/filterbutton.qss"); stylefile.open(QFile::ReadOnly);
	QString stylesheet(stylefile.readAll());

	deleteButton = new QPushButton;
	deleteButton->setText("X");
	deleteButton->setToolTip(tr("Remove This Filter"));
	deleteButton->setShortcut(tr("Del"));
	deleteButton->setStatusTip(tr("Remove This Filter"));
	deleteButton->setStyleSheet(stylesheet);
	return deleteButton;
}


QComboBox* FilterButton::createComboBox(const QStringList& options, const QString& currentOption)
{
	// Stylesheet
	QFile stylefile(":/qss/filterbutton.qss"); stylefile.open(QFile::ReadOnly);
	QString stylesheet(stylefile.readAll());

	filtersComboBox = new QComboBox;

	QListView * listView = new QListView(filtersComboBox);
	filtersComboBox->addItems(options);
	listView->setStyleSheet(stylesheet);


	filtersComboBox->setView(listView);
	filtersComboBox->setStyleSheet(stylesheet);

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
