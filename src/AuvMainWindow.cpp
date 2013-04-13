// AuvMainWindow.cpp
//
// Main Window for AUV software

#include "AuvMainWindow.h"
#include "FilterButton.h"
#include "FilterCamWidget.h"
#include "FilterChain.h"
#include "FilterCreator.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QFileDialog>
#include <iostream>

using namespace std;

AuvMainWindow::AuvMainWindow(void)
	: filterChain(NULL)
{
	filterCreator = new FilterCreator;

	createNewChain();
	createStatusBar();
	createMainLayout();
}

void AuvMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr(""));
}

void AuvMainWindow::open()
{
  
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open existing videos"),".",tr("(*.wmv);(*.mpg);Any image files (*)"));
	if (!fileName.isEmpty())
	loadFile(fileName);
  
}

void AuvMainWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("MyEditor"),tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return;
	}
	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	//textEdit->setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();
	//setCurrentFile(fileName);
	//statusBar()->showMessage(tr("File loaded"), 2000);
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
	FilterCamWidget *filterWidget = new FilterCamWidget(filterChain);
	filterWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	centralLeftWidgetLayout->addWidget(filterWidget);

	FilterCamWidget *filterWidget2 = new FilterCamWidget(filterChain);
	filterWidget2->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	centralLeftWidgetLayout->addWidget(filterWidget2);
	
	//	Connect filterWidget to backend
	connect(this, SIGNAL(filterListChanged(QStringList&)),
			filterWidget, SLOT(filterListChanged(QStringList&)));
	connect(this, SIGNAL(filterTypeChanged(int)),
			filterWidget, SLOT(filterTypeChanged(int)));
	connect(this, SIGNAL(filterListChanged(QStringList&)),
			filterWidget2, SLOT(filterListChanged(QStringList&)));
	connect(this, SIGNAL(filterTypeChanged(int)),
			filterWidget2, SLOT(filterTypeChanged(int)));
}


// Add a filter (and button) to the chain
void AuvMainWindow::appendFilterButton()
{
	// Create the filter
	filterChain->appendNewFilter();

	// Create the widgets
	const FilterCreator::StringList& filterNames = filterCreator->getFilterNames();
	QStringList filters;
	// Stupid hack to convert vector of strings to QStringList
	for (FilterCreator::StringList::const_iterator it=filterNames.begin(); it!=filterNames.end(); ++it) {
		filters << (*it).c_str();
	}
	QString btnName = QString("Filter") + QString::number(filterChain->getChain().size());
	FilterButton *filterButton = new FilterButton(btnName, filters);

	filterButton->listItem = filterList->addItem(filterButton);
  
	connect(filterButton, SIGNAL(deleteFilterButton(QListWidgetItem *)),
			this, SLOT(deleteItem(QListWidgetItem *)));
	connect(filterButton, SIGNAL(deleteFilterButton(QListWidgetItem *)),
			filterList, SLOT(deleteItem(QListWidgetItem *)));
	connect(filterButton, SIGNAL(selectionChanged(const QString&)),
			this, SLOT(changeFilterType(const QString&)));
}




void AuvMainWindow::createMiddleLayout()
{
	// Create the button for adding filters to the chain
	QPushButton *addFilterButton = new QPushButton;
	QPixmap pixmap(":/images/plusbutton.png");
	QIcon ButtonIcon(pixmap);
	addFilterButton->setIcon(ButtonIcon);
	addFilterButton->setIconSize(pixmap.rect().size());
	addFilterButton->setStyleSheet( "QPushButton{height:40px;border-style:outset;border-radius:10px;border-color: grey;border-width: 2px;background-color: #FFFFCC;}");
	//addFilterButton->setStyleSheet( "QPushButton:pressed {height:40px;border-style:inset;border-radius:10px;border-color: grey;border-width: 2px;}");

	filterList = new QListWidgetWithDrop;
	filterList->setStyleSheet("QWidget { background-color: #E6E6E0;  }");

	//	Drag and drop
	filterList->setSelectionMode(QAbstractItemView::SingleSelection);
	filterList->setDragEnabled(true);
	filterList->setDragDropMode(QAbstractItemView::InternalMove);
	filterList->viewport()->setAcceptDrops(true);
	filterList->setDropIndicatorShown(true);

	centralMiddleWidgetLayout->addWidget(filterList);
	centralMiddleWidgetLayout->addWidget(addFilterButton);

	connect(addFilterButton, SIGNAL(clicked()),
			this, SLOT(appendFilterButton()));

	//	Connect filterList to backend
//	connect(filterList,SIGNAL(listItemSwapped(int, int)),this,SLOT(listItemSwapped(int, int)));
//	connect(filterList,SIGNAL(listItemAdded()),this,SLOT(listItemAdded()));
//	connect(filterList,SIGNAL(listItemDeleted(int)),this,SLOT(listItemDeleted(int)));
	connect(filterList,SIGNAL(listItemAdded()),this,SLOT(listChanged()));
	connect(filterList,SIGNAL(listItemDeleted(int)),this,SLOT(listChanged()));
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
	QPixmap pixmap(":/images/record.jpg");
	QIcon ButtonIcon(pixmap);
	recordButton->setIcon(ButtonIcon);
	recordButton->setIconSize(pixmap.rect().size()*0.7);
        recordButton->setStyleSheet("QPushButton{color:black;height:35px;width:37px;border-style:outset;border-color: grey;border-radius: 5px;border-width:2px;background-color: #FFFFCC;}");

        
  
        //snapshot button
        snapshotButton = new QPushButton;
	QPixmap snapshotPixmap(":/images/snapshot.png");
	QIcon snapshotButtonIcon(snapshotPixmap);
	snapshotButton->setIcon(snapshotButtonIcon);
	snapshotButton->setIconSize(snapshotPixmap.rect().size()*0.7);
        snapshotButton->setStyleSheet("QPushButton{color:black;height:35px;width:35px;border-style:outset;border-color: grey;border-radius: 5px;border-width:2px;background-color: #FFFFCC;}");

        //open button
        openButton = new QPushButton;
	QPixmap openPixmap(":/images/open.png");
	QIcon openButtonIcon(openPixmap);
	openButton->setIcon(openButtonIcon);
	openButton->setIconSize(openPixmap.rect().size());
        openButton->setStyleSheet("QPushButton{color:black;height:35px;width:35px;border-style:outset;border-color: grey;border-radius: 5px;border-width:2px;background-color: #FFFFCC;}");
        connect(openButton,SIGNAL(clicked()),this,SLOT(open()));
  
        menuContentsLayout->addWidget(recordButton);
        menuContentsLayout->addWidget(snapshotButton);  
        menuContentsLayout->addWidget(openButton);       
 
    //Create menu button
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
    menuButton->setStyleSheet("QPushButton{color:black;height:40px;width:40px;border-style:outset;border-color: grey;border-radius: 5px;border-width:2px;background-color: #FFFFCC;}");
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
	filterChain = new FilterChain(filterCreator);
	filterChain->setStream(&stream);
}

void AuvMainWindow::listChanged()
{
	QStringList list;
	for (int i=0; i<filterList->count(); ++i) {
		QListWidgetItem *item = filterList->item(i);
		FilterButton *filterBtn = (FilterButton*)filterList->itemWidget(item);
		list << filterBtn->getName();
	}
	emit filterListChanged(list);
}

void AuvMainWindow::deleteItem(QListWidgetItem *item)
{
	int row = filterList->row(item);
	filterChain->removeFilter(filterChain->getChain()[row]);
}

void AuvMainWindow::changeFilterType(const QString& text)
{
	FilterButton *button = (FilterButton*)QObject::sender();
	int row = filterList->row(button->listItem);
	filterChain->changeFilterType(row, text.toStdString());

	emit filterTypeChanged(row);
}
