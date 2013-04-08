// AuvMainWindow.cpp
//
// Main Window for AUV software

#include "AuvMainWindow.h"
#include "FilterCamWidget.h"
#include <QtGui>
#include <QHBoxLayout>
#include <iostream>

using namespace std;

AuvMainWindow::AuvMainWindow(void)
{
	createStatusBar();
	createMainLayout();
}

void AuvMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr(""));
}

void AuvMainWindow::createMainLayout()
{
	//Set size
        setGeometry(0, 0, 800, 600);
    
        //Set main central horizontal widget/layout (horizontal)
        centralWidget = new QWidget;
        centralWidgetLayout = new QHBoxLayout;
	centralWidget->setLayout(centralWidgetLayout);
	centralWidget->setStyleSheet("QWidget { background-color: yellow; }");
	setCentralWidget(centralWidget);
	
	//Set centralWidget left, middle, right widget/layout (vertical)
	centralLeftWidget = new QWidget;
        centralLeftWidgetLayout = new QVBoxLayout;
	centralLeftWidget->setLayout(centralLeftWidgetLayout);
	centralLeftWidgetLayout->setAlignment(Qt::AlignTop);
	centralLeftWidget->setStyleSheet("QWidget { background-color: red; }");
	centralLeftScrollArea = new QScrollArea;
	centralLeftScrollArea->setWidget(centralLeftWidget);
	centralLeftScrollArea->setWidgetResizable(true);
	centralWidgetLayout->addWidget(centralLeftScrollArea);
	
	centralMiddleWidget = new QWidget;
        centralMiddleWidgetLayout = new QVBoxLayout;
	centralMiddleWidget->setLayout(centralMiddleWidgetLayout);
	centralMiddleWidgetLayout->setAlignment(Qt::AlignTop);
	centralMiddleWidget->setStyleSheet("QWidget { background-color: blue; }");
	centralMiddleScrollArea = new QScrollArea;
	centralMiddleScrollArea->setWidget(centralMiddleWidget);
	centralMiddleScrollArea->setWidgetResizable(true);
	centralWidgetLayout->addWidget(centralMiddleScrollArea);
	
	centralRightWidget = new QWidget;
        centralRightWidgetLayout = new QVBoxLayout;
	centralRightWidget->setLayout(centralRightWidgetLayout);
	centralRightWidget->setStyleSheet("QWidget { background-color: green; }");
	centralWidgetLayout->addWidget(centralRightWidget);
	centralRightWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	
	//Create individual layout contents
	createLeftLayout();
        createMiddleLayout();
	createRightLayout();
}

void AuvMainWindow::createLeftLayout()
{
	//	Add 2 filter widgets
	QStringList filters;
	filters << "Raw" << "Gray" << "Red";
	FilterCamWidget *filterWidget = new FilterCamWidget(&stream);
	filterWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	filterWidget->setFilterList(filters);
	centralLeftWidgetLayout->addWidget(filterWidget);
	
	FilterCamWidget *filterWidget2 = new FilterCamWidget(&stream);
	filterWidget2->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	filterWidget2->setFilterList(filters);
	centralLeftWidgetLayout->addWidget(filterWidget2);
}

void AuvMainWindow::moveFilterDown(QListWidgetItem *current) 
{
//    QListWidgetItem *current = filterList->currentItem();
    int currIndex = filterList->row(current);
    //Debug
    printf("%p %d %d\n", current, currIndex, filterList->count());
     if (currIndex >= filterList->count()-1)
	return;
   // QListWidgetItem *next = filterList->item(filterList->row(current) + 1);
   // int nextIndex = filterList->row(next);
   QWidget *t = filterList->itemWidget(current);
   //filterList->takeItem(currIndex);
//delete current;   
	QListWidgetItem *Listitem = new QListWidgetItem();
   filterList->insertItem(0,Listitem);
   filterList->setItemWidget(Listitem,t);
   Listitem->setSizeHint(t->size());
   ((CustomButton*)t)->listItem = Listitem;


printf("asd\n");
   filterList->removeItemWidget(current);
	delete current;
  // printf("t: %p\n", filterList->itemWidget(current));
   // filterList->insertItem(currIndex, temp);
}
     
void AuvMainWindow::moveFilterUp(QListWidgetItem *current) 
{
     //QListWidgetItem *current = (QListWidgetItem*)QObject::sender();//filterList->currentItem();
     int currIndex = filterList->row(current);
     //Debug
     printf("%p %d %d\n", current, currIndex, filterList->count());
   // QListWidgetItem *next = filterList->item(filterList->row(current) + 1);
   // int nextIndex = filterList->row(next);
     
    QListWidgetItem *temp = filterList->takeItem(currIndex);
   // filterList->insertItem(currIndex, temp);
if (currIndex > 0)
    filterList->insertItem(currIndex-1, temp);
}

void AuvMainWindow::createFilterDropdown()
{

  cb = new CustomButton;
  //cb->show();
  //centralMiddleWidgetLayout->addWidget(cb);
  QListWidgetItem *Listitem = new QListWidgetItem();
  filterList->addItem(Listitem);
  filterList->setItemWidget(Listitem,cb);
  Listitem->setSizeHint(cb->size());
  cb->listItem = Listitem;
  
  connect(cb,SIGNAL(moveFilterUp(QListWidgetItem *)),this,SLOT(moveFilterUp(QListWidgetItem *)));	
  connect(cb,SIGNAL(moveFilterDown(QListWidgetItem *)),this,SLOT(moveFilterDown(QListWidgetItem *)));	
}

void AuvMainWindow::createMiddleLayout()
{
QPushButton *myButton = new QPushButton;
QPixmap pixmap("plus.jpg");
QIcon ButtonIcon(pixmap);
myButton->setIcon(ButtonIcon);
myButton->setIconSize(pixmap.rect().size());
filterList = new QListWidget;
filterList->setStyleSheet("QWidget { background-color: pink; }");
centralMiddleWidgetLayout->addWidget(myButton);
centralMiddleWidgetLayout->addWidget(filterList);
connect(myButton,SIGNAL(clicked()),this,SLOT(createFilterDropdown()));	
}


void AuvMainWindow::createRightLayout(){
	//	Create Frames
	menuContents = new QWidget(centralRightWidget);
	menuContents->setStyleSheet("QWidget { background-color: pink; }");
	menuContents->setMaximumHeight(60);
	menuContentsLayout = new QHBoxLayout;
	menuContentsLayout->setAlignment(Qt::AlignRight);
	menuContents->setLayout(menuContentsLayout);
	rawVideoContents = new QWidget(centralRightWidget);
	rawVideoContents->setStyleSheet("QWidget { background-color: gray; }");
	settingsContents = new QWidget(centralRightWidget);
	settingsContents->setStyleSheet("QWidget { background-color: purple; }");
	centralRightWidgetLayout->addWidget(menuContents);
	centralRightWidgetLayout->addWidget(rawVideoContents);
	centralRightWidgetLayout->addWidget(settingsContents);

	//	Create menu button
    menuButton = new QPushButton(menuContents);
    menuButton->setGeometry(QRect(0, 0, 40, 40));
    menuButton->setMaximumWidth(40);
    menuButton->setMaximumHeight(40);
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(false);
    font.setWeight(75);
    menuButton->setFont(font);
    menuButton->setIconSize(QSize(20, 20));
    menuButton->setCheckable(false);
    menuButton->setText(QApplication::translate("AuvMainWindow", "\342\211\241", 0, QApplication::UnicodeUTF8));
    menuContentsLayout->addWidget(menuButton);
        
	//	Create raw video feed widget
	rawCamWidget = new CamWidget;
    rawCamWidget->setParent(rawVideoContents);
    QObject::connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)), rawCamWidget, SLOT(setImage(const cv::Mat&)));
}


void AuvMainWindow::print(){
	cout << centralWidget->sizeIncrement().width() << endl;
	cout << centralLeftWidget->sizeIncrement().width() << endl;
	cout << centralMiddleWidget->sizeIncrement().width() << endl;
	cout << centralRightWidget->sizeIncrement().width() << endl;
}
