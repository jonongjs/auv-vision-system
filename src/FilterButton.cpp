#include <QtGui>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include "FilterButton.h"

FilterButton::FilterButton(const QString& name, const QStringList& options, QWidget *parent)
	: QWidget(parent)
{
	deleteButton = createDeleteButton();

	filtersComboBox = createComboBox(options);

	numberLabel = new QLabel(name);
	numberLabel->setStyleSheet("QLabel{color:black;height:20px;length:20px;background-color: #FFFFCC;}");

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
	//QPixmap pixmap("uparrow.png");
	//QIcon ButtonIcon(pixmap);
	//deleteButton->setIcon(ButtonIcon);
	//deleteButton->setIconSize(pixmap.rect().size());
	deleteButton->setText("X");
	deleteButton->setStyleSheet("QPushButton{color:white;height:20px;length:20px;border-style:outset;border-color: grey;border-radius: 1px;border-width: 2px;background-color: #FF8080;}");
	return deleteButton;
}


QComboBox* FilterButton::createComboBox(const QStringList& options)
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
	// filtersComboBox->lineEdit()->setReadOnly(true);
	filtersComboBox->setStyleSheet("QComboBox{background-color:white;width:30px;selection-background-color: lightgray;}");
	//filtersComboBox->setStyleSheet("QComboBox QAbstractItemView { outline:none;}");

	// Connect the combobox's signal to our own
	connect(filtersComboBox, SIGNAL(currentIndexChanged(const QString&)),
			this, SIGNAL(selectionChanged(const QString&)));

	return filtersComboBox;
}

QString FilterButton::getName()
{
	return numberLabel->text();
}
