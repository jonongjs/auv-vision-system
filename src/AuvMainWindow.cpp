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
	QString fileName = QFileDialog::getOpenFileName(this,
				tr("Open existing videos"),".",
				tr( "MPG videos (*.mpg *.mp4);;"
					"Any file (*)"));
	if (!fileName.isEmpty())
		loadFile(fileName);
}

void AuvMainWindow::loadFile(const QString &fileName)
{
	if (!stream.useVideo(fileName.toStdString()))
	{
		QMessageBox::warning(this, tr("AUV Vision System"),tr("Cannot read file %1.").arg(fileName));
		return;
	}
	statusBar()->showMessage(tr("File loaded"), 2000);
}

void AuvMainWindow::createMainLayout()
{
	//Set size
	setGeometry(0, 0, 800, 600);

	//Set main central horizontal widget/layout (horizontal)
	centralWidget = new QWidget;
	centralWidgetLayout = new QHBoxLayout;
	centralWidget->setLayout(centralWidgetLayout);
	centralWidget->setStyleSheet("QWidget { background-color: #D6C299; }");
	setCentralWidget(centralWidget);
	
	//Set centralWidget left, middle, right widget/layout (vertical)
	centralLeftWidget = new QWidget;
	centralLeftWidgetLayout = new QVBoxLayout;
	centralLeftWidget->setLayout(centralLeftWidgetLayout);
	centralLeftWidgetLayout->setAlignment(Qt::AlignTop);
	centralLeftWidget->setStyleSheet("QWidget { background-color: #F3E6E0;  }");
	centralLeftScrollArea = new QScrollArea;
	centralLeftScrollArea->setWidget(centralLeftWidget);
	centralLeftScrollArea->setWidgetResizable(true);
	centralWidgetLayout->addWidget(centralLeftScrollArea);
	
	centralMiddleWidget = new QWidget;
	centralMiddleWidgetLayout = new QVBoxLayout;
	centralMiddleWidget->setLayout(centralMiddleWidgetLayout);
	centralMiddleWidgetLayout->setAlignment(Qt::AlignTop);
	centralMiddleWidget->setStyleSheet("QWidget { background-color: #F3E6E0;  }");
	centralMiddleScrollArea = new QScrollArea;
	centralMiddleScrollArea->setWidget(centralMiddleWidget);
	centralMiddleScrollArea->setWidgetResizable(true);
	centralWidgetLayout->addWidget(centralMiddleScrollArea);
	
	centralRightWidget = new QWidget;
	centralRightWidgetLayout = new QVBoxLayout;
	centralRightWidget->setLayout(centralRightWidgetLayout);
	centralRightWidget->setStyleSheet("QWidget { background-color: #F3E6E0; }");
	centralWidgetLayout->addWidget(centralRightWidget);
	centralRightWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	
	//Create individual layout contents
	createLeftLayout();
	createMiddleLayout();
	createRightLayout();
}

void AuvMainWindow::createLeftLayout()
{
	//Add 2 filter widgets
	QLabel *label=new QLabel("    Selected Filter");
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
	FilterCamWidget *filterWidget = new FilterCamWidget(filterChain);
	filterWidget->setStyleSheet("QWidget {background-color:#F9F2F0;border-radius:10px;}");
	filterWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	centralLeftWidgetLayout->addWidget(label);
	centralLeftWidgetLayout->addWidget(filterWidget);

	QLabel *label2=new QLabel("    Cumulative Filters");
	label2->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
	FilterCamWidget *filterWidget2 = new FilterCamWidget(filterChain);
	filterWidget2->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	centralLeftWidgetLayout->addWidget(label2);
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
        addFilterButton->setToolTip(tr("Add Filters To Your Video"));
	addFilterButton->setIcon(ButtonIcon);
	addFilterButton->setIconSize(pixmap.rect().size());
	//addFilterButton->setStyleSheet( "QPushButton{height:40px;border-style:outset;border-radius:10px;border-color: grey;border-width: 2px;background-color: #FFFFCC;}");
	addFilterButton->setStyleSheet("QPushButton {height:40px;border: 2px solid gray;border-style:outset;border-radius: 6px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFCC, stop: 1 #FFFFFF);} QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}");

	filterList = new QListWidgetWithDrop;
	//filterList->setStyleSheet("QWidget { background-color: #F3E6E0;  }");
	filterList->setStyleSheet("QWidget {background-color:#F9F2F0;border-radius:10px;}");

	//	Drag and drop
	filterList->setSelectionMode(QAbstractItemView::SingleSelection);
	filterList->setDragEnabled(true);
	filterList->setDragDropMode(QAbstractItemView::InternalMove);
	filterList->viewport()->setAcceptDrops(true);
	filterList->setDropIndicatorShown(true);

	QLabel *label=new QLabel("    Add Filters");
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
	centralMiddleWidgetLayout->addWidget(label);
	centralMiddleWidgetLayout->addWidget(filterList);
	centralMiddleWidgetLayout->addWidget(addFilterButton);

	connect(addFilterButton, SIGNAL(clicked()),
			this, SLOT(appendFilterButton()));

	//	Connect filterList to backend
//	connect(filterList,SIGNAL(listItemSwapped(int, int)),this,SLOT(listItemSwapped(int, int)));
//	connect(filterList,SIGNAL(listItemAdded()),this,SLOT(listItemAdded()));
//	connect(filterList,SIGNAL(listItemDeleted(int)),this,SLOT(listItemDeleted(int)));
	connect(filterList, SIGNAL(listItemMoved(int, int)),
			this, SLOT(listItemMoved(int, int)));
	connect(filterList, SIGNAL(listItemAdded()), this, SLOT(listChanged()));
	connect(filterList, SIGNAL(listItemDeleted(int)), this, SLOT(listChanged()));
}


void AuvMainWindow::createRightLayout(){
	//	Create Frames
	/*QVBoxLayout *labelLayout = new QVBoxLayout;
	  labelLayout->setAlignment(Qt::AlignRight);
	  QLabel *labelHeading=new QLabel("Video Stream");
	  labelHeading->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
	  labelHeading->setLayout(labelLayout);
	  centralRightWidgetLayout->addWidget(labelHeading);*/

	menuContents = new QWidget(centralRightWidget);
	menuContents->setStyleSheet("QWidget { background-color:#F9F2F0;border-radius:10px;}");
	menuContents->setMaximumHeight(60);
	menuContentsLayout = new QHBoxLayout;
	menuContentsLayout->setAlignment(Qt::AlignRight);
	menuContents->setLayout(menuContentsLayout);
        
	rawVideoContents = new QWidget(centralRightWidget);
	rawVideoContents->setStyleSheet("QWidget { background-color: #FFFFFF; }");

	settingsContents = new QWidget(centralRightWidget);
	settingsContents->setStyleSheet("QWidget { background-color:#F9F2F0;border-radius:10px;}");

	centralRightWidgetLayout->addWidget(menuContents);
	centralRightWidgetLayout->addWidget(rawVideoContents);
	centralRightWidgetLayout->addWidget(settingsContents);

	// videorecording button
	recordButton = new QPushButton;
	QPixmap pixmap(":/images/record.jpg");
	QIcon ButtonIcon(pixmap);
	recordButton->setIcon(ButtonIcon);
	recordButton->setIconSize(pixmap.rect().size()*0.7);
	recordButton->setToolTip(tr("Start Recording Your Live Stream "));
	recordButton->setStyleSheet("QPushButton {height:37px;width:37px;border: 2px solid gray;border-style:outset;border-radius: 5px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFCC, stop: 1 #FFFFFF);} QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}");
//	connect(recordButton, SIGNAL(clicked()), this, SLOT(startRecording()));
  
	// snapshot button
	snapshotButton = new QPushButton;
	QPixmap snapshotPixmap(":/images/snapshot.png");
	QIcon snapshotButtonIcon(snapshotPixmap);
	snapshotButton->setIcon(snapshotButtonIcon);
	snapshotButton->setToolTip(tr("Take a Snapshot Of Your Live Stream "));
	snapshotButton->setIconSize(snapshotPixmap.rect().size()*0.7);
	snapshotButton->setStyleSheet("QPushButton {height:35px;width:35px;border: 2px solid gray;border-style:outset;border-radius: 5px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFCC, stop: 1 #FFFFFF);} QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}");
	connect(snapshotButton, SIGNAL(clicked()), this, SLOT(takeSnapshot()));

	//open button
	openButton = new QPushButton;
	QPixmap openPixmap(":/images/open.png");
	QIcon openButtonIcon(openPixmap);
	openButton->setIcon(openButtonIcon);
	openButton->setToolTip(tr("Open An Existing Video "));
	openButton->setIconSize(openPixmap.rect().size());
	openButton->setStyleSheet("QPushButton {height:35px;width:35px;border: 2px solid gray;border-style:outset;border-radius: 5px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFCC, stop: 1 #FFFFFF);} QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}");
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
    menuButton->setToolTip(tr("Additional Options "));
    menuButton->setText(QApplication::translate("AuvMainWindow", "\342\211\241", 0, QApplication::UnicodeUTF8));
    menuButton->setStyleSheet("QPushButton {height:40px;width:40px;border: 2px solid gray;border-style:outset;border-radius: 5px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFCC, stop: 1 #FFFFFF);} QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa);}");
    //connect(menuButton,SIGNAL(clicked()),this,SLOT(displaySaveSettings()));	
//    connect(menuButton,SIGNAL(clicked()),this,SLOT(displayMenu()));	
    menuContentsLayout->addWidget(menuButton);
        
	//	Create raw video feed widget
	rawCamWidget = new CamWidget;
    rawCamWidget->setParent(rawVideoContents);
    QObject::connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)), rawCamWidget, SLOT(setImage(const cv::Mat&)));
    
    //	Settings widget
    settingWidget = new FilterSettingWidget;
    settingWidget->setParent(settingsContents);
	settingWidget->chain = filterChain;
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

void AuvMainWindow::listItemMoved(int fromRow, int toRow)
{
	filterChain->moveFilter(fromRow, toRow);
	listChanged();
}


void AuvMainWindow::deleteItem(QListWidgetItem *item)
{
	int row = filterList->row(item);
	filterChain->removeFilter(row);
}

void AuvMainWindow::changeFilterType(const QString& text)
{
	FilterButton *button = (FilterButton*)QObject::sender();
	int row = filterList->row(button->listItem);
	filterChain->changeFilterType(row, text.toStdString());

	emit filterTypeChanged(row);
}

void AuvMainWindow::takeSnapshot()
{
	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	stream.writeImage((timestamp+".jpg").toStdString());
}

void AuvMainWindow::startRecording()
{
	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
}
