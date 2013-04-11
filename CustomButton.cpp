#include <QtGui>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include "CustomButton.h"

CustomButton::CustomButton(QWidget *parent): QWidget(parent)
{
	deleteButton = createDeleteButton();

	filtersComboBox = createComboBox();

	numberLabel = new QLabel(tr("F1:"));

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(deleteButton);
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(numberLabel);
	topLeftLayout->addWidget(filtersComboBox);
	topLeftLayout->addLayout(rightLayout);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(topLeftLayout);
	setLayout(mainLayout);

	connect(deleteButton,SIGNAL(clicked()),this,SLOT(buttonDelete()));		
}

void CustomButton::buttonDelete()
{
	emit deleteFilterDropdown(listItem);
}


 QPushButton *CustomButton::createDeleteButton()
 {
	deleteButton = new QPushButton;
	//QPixmap pixmap("uparrow.png");
	//QIcon ButtonIcon(pixmap);
	//deleteButton->setIcon(ButtonIcon);
	//deleteButton->setIconSize(pixmap.rect().size());
	deleteButton->setText("X");
    return deleteButton;
 }


 QComboBox *CustomButton::createComboBox()
 {
	QLabel label("F1"); // create label
	label.show();

	filtersComboBox = new QComboBox;
	
	QListView * listView = new QListView(filtersComboBox);
	filtersComboBox->addItem("Greyscale");
	filtersComboBox->addItem("Red");
	filtersComboBox->addItem("Sepia");
	filtersComboBox->addItem("Invert");
	listView->setStyleSheet("QListView::item {     \
	border-bottom: 5px solid white; margin:3px; }  \
	QListView::item:selected {                     \
	border-bottom: 5px solid black; margin:3px;    \
	color: black;                                  \
	}                                              \
	");
	filtersComboBox->setView(listView);
        return filtersComboBox;
 }


