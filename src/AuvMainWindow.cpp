// AuvMainWindow.cpp
//
// Main Window for AUV software

#include "AuvMainWindow.h"
#include "FilterButton.h"
#include "FilterCamWidget.h"
#include "FilterChain.h"
#include <QtGui>
#include <QHBoxLayout>
#include <iostream>

using namespace std;

AuvMainWindow::AuvMainWindow(void)
	: filterChain(NULL)
{
	createNewChain();
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
	centralWidget->setStyleSheet("QWidget { background-color: #FFFFCC; }");
	setCentralWidget(centralWidget);
	
	//Set centralWidget left, middle, right widget/layout (vertical)
	centralLeftWidget = new QWidget;
    centralLeftWidgetLayout = new QVBoxLayout;
	centralLeftWidget->setLayout(centralLeftWidgetLayout);
	centralLeftWidgetLayout->setAlignment(Qt::AlignTop);
	centralLeftWidget->setStyleSheet("QWidget { background-color: #E6E6E0;  }");
	centralLeftScrollArea = new QScrollArea;
	centralLeftScrollArea->setWidget(centralLeftWidget);
	centralLeftScrollArea->setWidgetResizable(true);
	centralWidgetLayout->addWidget(centralLeftScrollArea);
	
	centralMiddleWidget = new QWidget;
    centralMiddleWidgetLayout = new QVBoxLayout;
	centralMiddleWidget->setLayout(centralMiddleWidgetLayout);
	centralMiddleWidgetLayout->setAlignment(Qt::AlignTop);
	centralMiddleWidget->setStyleSheet("QWidget { background-color: #E6E6E0;  }");
	centralMiddleScrollArea = new QScrollArea;
	centralMiddleScrollArea->setWidget(centralMiddleWidget);
	centralMiddleScrollArea->setWidgetResizable(true);
	centralWidgetLayout->addWidget(centralMiddleScrollArea);
	
	centralRightWidget = new QWidget;
    centralRightWidgetLayout = new QVBoxLayout;
	centralRightWidget->setLayout(centralRightWidgetLayout);
	centralRightWidget->setStyleSheet("QWidget { background-color: #E6E6E0; }");
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
	filters << "GaussianBlur" << "Gray" << "HSV";
	FilterCamWidget *filterWidget = new FilterCamWidget(&stream);
	filterWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	filterWidget->setFilterList(filters);
	centralLeftWidgetLayout->addWidget(filterWidget);
	
	FilterCamWidget *filterWidget2 = new FilterCamWidget(&stream);
	filterWidget2->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	filterWidget2->setFilterList(filters);
	centralLeftWidgetLayout->addWidget(filterWidget2);
	
	//	Connect filterWidget to backend
	//connect(backend,SIGNAL(filterListChanged(QStringList filterList)),filterWidget,SLOT(filterListChanged(QStringList filterList)));
	//connect(backend,SIGNAL(filterListChanged(QStringList filterList)),filterWidget2,SLOT(filterListChanged(QStringList filterList)));
}


void AuvMainWindow::createFilterDropdown()
{
	FilterButton *cb = new FilterButton;
	QListWidgetItem *Listitem = new QListWidgetItem();
	filterList->addItem(Listitem);
	filterList->setItemWidget(Listitem,cb);
	Listitem->setSizeHint(cb->size());
	cb->listItem = Listitem;
  
	connect(cb,SIGNAL(deleteFilterDropdown(QListWidgetItem *)),filterList,SLOT(deleteItem(QListWidgetItem *)));
}




void AuvMainWindow::createMiddleLayout()
{
QPushButton *myButton = new QPushButton;
QPixmap pixmap("plusbutton.png");
QIcon ButtonIcon(pixmap);
myButton->setIcon(ButtonIcon);
myButton->setIconSize(pixmap.rect().size());
myButton->setStyleSheet( "QPushButton{height:40px;border-style:outset;border-radius:10px;border-color: grey;border-width: 2px;background-color: #FFFFCC;}");
//myButton->setStyleSheet( "QPushButton:pressed {height:40px;border-style:inset;border-radius:10px;border-color: grey;border-width: 2px;}");

filterList = new QListWidgetWithDrop;
filterList->setStyleSheet("QWidget { background-color: #E6E6E0;  }");

//	Drag and drop
filterList->setSelectionMode(QAbstractItemView::SingleSelection);
filterList->setDragEnabled(true);
filterList->setDragDropMode(QAbstractItemView::InternalMove);
filterList->viewport()->setAcceptDrops(true);
filterList->setDropIndicatorShown(true);

centralMiddleWidgetLayout->addWidget(filterList);
centralMiddleWidgetLayout->addWidget(myButton);

connect(myButton,SIGNAL(clicked()),this,SLOT(createFilterDropdown()));

//	Connect filterList to backend
//connect(filterList,SIGNAL(listItemSwapped(int, int)),this,SLOT(listItemSwapped(int, int)));
//connect(filterList,SIGNAL(listItemAdded()),this,SLOT(listItemAdded()));
//connect(filterList,SIGNAL(listItemDeleted(int)),this,SLOT(listItemDeleted(int)));
}


void AuvMainWindow::createRightLayout(){
	//	Create Frames
	menuContents = new QWidget(centralRightWidget);
	menuContents->setStyleSheet("QWidget { background-color: #E6E6E0; }");
	menuContents->setMaximumHeight(60);
	menuContentsLayout = new QHBoxLayout;
	menuContentsLayout->setAlignment(Qt::AlignRight);
	menuContents->setLayout(menuContentsLayout);
	rawVideoContents = new QWidget(centralRightWidget);
	rawVideoContents->setStyleSheet("QWidget { background-color: #E6E6E0; }");
	settingsContents = new QWidget(centralRightWidget);
	settingsContents->setStyleSheet("QWidget { background-color: #E6E6E0; }");
	centralRightWidgetLayout->addWidget(menuContents);
	centralRightWidgetLayout->addWidget(rawVideoContents);
	centralRightWidgetLayout->addWidget(settingsContents);



   //videorecording button
        recordButton = new QPushButton;
	QPixmap pixmap("recordicon.png");
	QIcon ButtonIcon(pixmap);
	recordButton->setIcon(ButtonIcon);
	recordButton->setIconSize(pixmap.rect().size());
        
  
   //snapshot button
  snapshotButton = new QPushButton;
	QPixmap pixmap2("downarrow.png");
	QIcon ButtonIcon2(pixmap);
	snapshotButton->setIcon(ButtonIcon2);
	snapshotButton->setIconSize(pixmap2.rect().size());
  
  menuContentsLayout->addWidget(recordButton);
  menuContentsLayout->addWidget(snapshotButton);       
 






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
    menuButton->setStyleSheet("QPushButton{color:black;height:30px;length:30px;border-style:outset;border-color: grey;border-radius: 1px;border-width:   2px;background-color: #FFFFCC;}");
    connect(menuButton,SIGNAL(clicked()),this,SLOT(displaySaveSettings()));	
    menuContentsLayout->addWidget(menuButton);
        
	//	Create raw video feed widget
	rawCamWidget = new CamWidget;
    rawCamWidget->setParent(rawVideoContents);
    QObject::connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)), rawCamWidget, SLOT(setImage(const cv::Mat&)));
    
    //	Settings widget
    settingWidget = new FilterSettingWidget;
    settingWidget->setParent(settingsContents);
    connect(filterList, SIGNAL(currentRowChanged(int)), settingWidget, SLOT(filterChanged(int)));
}

void AuvMainWindow::displaySaveSettings()
{
	popup = new SavePopup;
	popup->show();
}


void AuvMainWindow::createNewChain()
{
	//TODO: make new chains?
	filterChain = new FilterChain;
}

