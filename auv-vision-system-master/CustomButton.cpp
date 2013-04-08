#include <QtGui>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include "CustomButton.h"

 CustomButton::CustomButton(QWidget *parent): QWidget(parent)
 {
        upButton = createupButton();
        downButton = createdownButton();

        filtersComboBox = createComboBox();
    
        numberLabel = new QLabel(tr("F1:"));
   
	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(upButton);
	rightLayout->addWidget(downButton);
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(numberLabel);
	topLeftLayout->addWidget(filtersComboBox);
	topLeftLayout->addLayout(rightLayout);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(topLeftLayout);
	setLayout(mainLayout);

        connect(upButton,SIGNAL(clicked()),this,SLOT(buttonUp()));	
        connect(downButton,SIGNAL(clicked()),this,SLOT(buttonDown()));	

 }

void CustomButton::buttonUp()
{
	printf("hello\n");
	emit moveFilterUp(listItem);
}

void CustomButton::buttonDown()
{
	printf("bye\n");
	emit moveFilterDown(listItem);
}


 QPushButton *CustomButton::createupButton()
 {
	upButton = new QPushButton;
	QPixmap pixmap("uparrow.png");
	QIcon ButtonIcon(pixmap);
	upButton->setIcon(ButtonIcon);
	upButton->setIconSize(pixmap.rect().size());
        return upButton ;
 }

QPushButton *CustomButton::createdownButton()
 {
        downButton = new QPushButton;
	QPixmap pixmap("downarrow.png");
	QIcon ButtonIcon(pixmap);
	downButton->setIcon(ButtonIcon);
	downButton->setIconSize(pixmap.rect().size());
        return downButton;
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


