// AuvMainWindow.cpp
//
// Main Window for AUV software

#include "AuvMainWindow.h"
#include "ChainSerializer.h"
#include "FilterButton.h"
#include "FilterCamWidget.h"
#include "FilterChain.h"
#include "FilterCreator.h"
#include "HelpWidget.h"

#include <QApplication>
#include <QDateTime>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRect>
#include <QStatusBar>
#include <iostream>

using namespace std;

AuvMainWindow::AuvMainWindow(void)
	: filterChain(NULL), isRecording(0)
{
	filterCreator = new FilterCreator;

	createNewChain();
	createStatusBar();
	createMainLayout();
}

// Widget creation methods

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
	QLabel *label = new QLabel("Filter Output 1");
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;margin-top:18px;}");
	filterWidget = new FilterCamWidget(filterChain);
	filterWidget->setStyleSheet("QWidget {background-color:#F9F2F0;border-radius:10px;}");
	filterWidget->setSizePolicy(centralMiddleScrollArea->sizePolicy());
	centralLeftWidgetLayout->addWidget(label);
	centralLeftWidgetLayout->addWidget(filterWidget);

	QLabel *label2 = new QLabel("Filter Output 2");
	label2->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");
	filterWidget2 = new FilterCamWidget(filterChain);
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

void AuvMainWindow::createMiddleLayout()
{
	// Stylesheets
	QFile stylefile(":/qss/addfilterbutton.qss"); stylefile.open(QFile::ReadOnly);
	QFile stylefile2(":/qss/buttonstyles.qss"); stylefile2.open(QFile::ReadOnly);
	QString stylesheet(stylefile.readAll());
	QString stylesheet2(stylefile2.readAll());

	// Create the button for adding filters to the chain
	QPushButton *addFilterButton = new QPushButton;
	QPixmap pixmap(":/images/plusbutton.png");
	QIcon ButtonIcon(pixmap);
	addFilterButton->setToolTip(tr("Add Filters To Your Video"));
	addFilterButton->setShortcut(tr("Ctrl+N"));
	addFilterButton->setStatusTip(tr("Add Filters To Your Video"));
	addFilterButton->setIcon(ButtonIcon);
	addFilterButton->setIconSize(pixmap.rect().size());
	addFilterButton->setStyleSheet(stylesheet);

	filterList = new QListWidgetWithDrop;
	//filterList->setStyleSheet("QWidget { background-color: #F3E6E0;  }");
	filterList->setStyleSheet("QWidget {background-color:#F9F2F0;border-radius:10px;}");

	//	Drag and drop
	filterList->setSelectionMode(QAbstractItemView::SingleSelection);
	filterList->setDragEnabled(true);
	filterList->setDragDropMode(QAbstractItemView::InternalMove);
	filterList->viewport()->setAcceptDrops(true);
	filterList->setDropIndicatorShown(true);

	middleMenuContents = new QWidget(centralRightWidget);
	middleMenuContents->setMaximumHeight(60);
	middleMenuContentsLayout = new QHBoxLayout; 
	middleMenuContentsLayout->setAlignment(Qt::AlignTop);
	middleMenuContents->setLayout(middleMenuContentsLayout);

	QLabel *label = new QLabel("    Add Filters");
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;}");

	middleMenuButton = new QToolButton(middleMenuContents);
	middleMenuButton->setGeometry(QRect(0, 0, 40, 40));
	middleMenuButton->setMaximumWidth(40);
	middleMenuButton->setMaximumHeight(40);
	QFont font;
	font.setPointSize(20);
	font.setBold(true);
	font.setItalic(false);
	font.setWeight(75);
	middleMenuButton->setFont(font);
	middleMenuButton->setIconSize(QSize(20, 20));
	middleMenuButton->setCheckable(false);
	middleMenuButton->setToolTip(tr("Additional Options "));
	middleMenuButton->setShortcut(tr("Ctrl+M"));
	middleMenuButton->setStatusTip(tr("Additional Options "));
	middleMenuButton->setText(QApplication::translate("AuvMainWindow", "\342\211\241", 0, QApplication::UnicodeUTF8));
	middleMenuButton->setStyleSheet(stylesheet2);

	createFiltersMenu();

	middleMenuContentsLayout->addWidget(label);
	middleMenuContentsLayout->addWidget(middleMenuButton);

	centralMiddleWidgetLayout->addWidget(middleMenuContents);
	//centralMiddleWidgetLayout->addWidget(menuButton);

	centralMiddleWidgetLayout->addWidget(filterList);
	centralMiddleWidgetLayout->addWidget(addFilterButton);

	connect(addFilterButton, SIGNAL(clicked()),
			this, SLOT(appendFilterButton()));

	// Connect filterList to backend
	connect(filterList, SIGNAL(listItemMoved(int, int)),
			this, SLOT(listItemMoved(int, int)));
	connect(filterList, SIGNAL(listItemAdded()), this, SLOT(listChanged()));
	connect(filterList, SIGNAL(listItemDeleted(int)), this, SLOT(listChanged()));
}

void AuvMainWindow::createRightLayout()
{     
	menuContents = new QWidget(centralRightWidget);
	menuContents->setStyleSheet("QWidget { background-color:#F9F2F0;border-radius:10px;}");
	menuContents->setMaximumHeight(60);
	menuContentsLayout = new QHBoxLayout;
	menuContentsLayout->setAlignment(Qt::AlignRight);
	menuContents->setLayout(menuContentsLayout);


	rawVideoContents = new QWidget(centralRightWidget);
	rawVideoLayout = new QVBoxLayout;

	rawVideoContents->setLayout(rawVideoLayout);	

	//	Settings widget
	settingWidget = new FilterSettingWidget(centralRightWidget);
	settingWidget->list = filterList;
	settingWidget->chain = filterChain;
	connect(filterList, SIGNAL(currentRowChanged(int)), settingWidget, SLOT(filterChanged(int)));
	connect(this, SIGNAL(filterTypeChanged(int)), settingWidget, SLOT(filterChanged()));

	centralRightWidgetLayout->addWidget(menuContents);
	centralRightWidgetLayout->addWidget(rawVideoContents);
	centralRightWidgetLayout->addWidget(settingWidget);

	createButtons();

	//	Create raw video feed widget and heading
	QLabel *rawLabel = new QLabel("Raw Video Input");
	rawLabel->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;height:30px}");

	rawVideoLayout->setAlignment(Qt::AlignTop);
	rawVideoLayout->addWidget(rawLabel);
	rawCamWidget = new CamWidget;
	rawVideoLayout->addWidget(rawCamWidget);
	connect(&stream, SIGNAL(imageUpdated(const cv::Mat&)),
			rawCamWidget, SLOT(setImage(const cv::Mat&)));
}

void AuvMainWindow::createButtons()
{
	// Load button styles
	QFile stylefile(":/qss/buttonstyles.qss");
	stylefile.open(QFile::ReadOnly);
	QString stylesheet(stylefile.readAll());

	// videorecording button
	recordButton = new QToolButton;
	QIcon *ico = new QIcon();
	ico->addPixmap(QPixmap(":/images/record.png"), QIcon::Normal, QIcon::Off);
	ico->addPixmap(QPixmap(":/images/stop.png"), QIcon::Normal, QIcon::On);
	recordButton->setIcon(*ico);
	recordButton->setCheckable(true);
	QPixmap pixmap(":/images/record.png");
	recordButton->setIconSize(pixmap.rect().size()*0.7);
	recordButton->setToolTip(tr("Record Your Video Stream "));
	recordButton->setShortcut(tr("Alt+R"));
	recordButton->setStatusTip(tr("Record Your Video Stream Into Your Current Directory By Pressing Start And Stop"));
	recordButton->setStyleSheet(stylesheet);
	connect(recordButton, SIGNAL(clicked()), this, SLOT(toggleRecording()));

	// snapshot button
	snapshotButton = new QPushButton;
	QPixmap snapshotPixmap(":/images/snapshot.png");
	snapshotButton->setIcon(QIcon(snapshotPixmap));
	snapshotButton->setToolTip(tr("Take a Snapshot Of Your Video Stream "));
	snapshotButton->setShortcut(tr("Alt+S"));
	snapshotButton->setStatusTip(tr("Take a Snapshot Of Your Video Stream Into Your Current Directory"));
	snapshotButton->setIconSize(snapshotPixmap.rect().size()*0.8);
	snapshotButton->setStyleSheet(stylesheet);
	connect(snapshotButton, SIGNAL(clicked()), this, SLOT(takeSnapshot()));

	// open button
	openButton = new QToolButton;
	QPixmap openPixmap(":/images/open.png");
	openButton->setIcon(QIcon(openPixmap));
	openButton->setToolTip(tr("Open An Existing Video "));
	openButton->setShortcut(tr("Ctrl+O"));
	openButton->setStatusTip(tr("Open An Existing Video Or Reset To Camera Stream "));
	openButton->setIconSize(openPixmap.rect().size()*0.5);
	openButton->setStyleSheet(stylesheet);

	createOpenMenu();

	menuContentsLayout->addWidget(recordButton);
	menuContentsLayout->addWidget(snapshotButton);  
	menuContentsLayout->addWidget(openButton);       

	//	Settings widget
	settingWidget->chain = filterChain;
	connect(filterList, SIGNAL(currentRowChanged(int)), settingWidget, SLOT(filterChanged(int)));
	connect(this, SIGNAL(filterTypeChanged(int)),
			settingWidget, SLOT(filterChanged()));

	//Create menu button
	menuButton = new QToolButton(menuContents);
	menuButton->setMaximumWidth(40);
	menuButton->setMaximumHeight(40);
	QFont font;
	font.setPointSize(20);
	font.setBold(true);
	font.setItalic(false);
	font.setWeight(75);
	menuButton->setFont(font);
	QPixmap menuPixmap(":/images/settings.png");
	menuButton->setIcon(QIcon(menuPixmap));
	menuButton->setIconSize(menuPixmap.rect().size()*2);
	menuButton->setCheckable(false);
	menuButton->setToolTip(tr("Additional Options "));
	menuButton->setShortcut(tr("Ctrl+M"));
	menuButton->setStatusTip(tr("Additional Options "));
	menuButton->setText(QApplication::translate("AuvMainWindow", "\342\211\241", 0, QApplication::UnicodeUTF8));
	menuButton->setStyleSheet(stylesheet);

	createSettingsMenu();
	menuContentsLayout->addWidget(menuButton);
}

void AuvMainWindow::createSettingsMenu()
{
	QMenu *popupMenu = new QMenu;

	/*
	   QAction *act1 = new QAction("Choose Directory to Save         ",this);
	   popupMenu->addAction(act1);
	   connect(act1, SIGNAL(triggered()), this, SLOT(displaySaveSettings()));
	 */

	QAction *act2 = new QAction("Help          ",this);
	popupMenu->addAction(act2);
	connect(act2, SIGNAL(triggered()), this, SLOT(displayHelp()));

	menuButton->setPopupMode(QToolButton::InstantPopup);
	menuButton->setMenu(popupMenu);
}

void AuvMainWindow::createFiltersMenu()
{
	filtersMenu = new QMenu;

	QAction *act1 = new QAction("Save Current Filter List         ",this);
	filtersMenu->addAction(act1);
	connect(act1, SIGNAL(triggered()), this, SLOT(saveChain()));

	QAction *act2 = new QAction("Load Existing Filter List         ",this);
	filtersMenu->addAction(act2);
	connect(act2, SIGNAL(triggered()), this, SLOT(loadChain()));

	middleMenuButton->setPopupMode(QToolButton::InstantPopup);
	middleMenuButton->setMenu(filtersMenu);
}

void AuvMainWindow::createOpenMenu()
{
	QMenu *popupMenu = new QMenu;

	QAction *act1 = new QAction("Upload Existing Video         ",this);
	popupMenu->addAction(act1);
	connect(act1, SIGNAL(triggered()), this, SLOT(open()));

	QAction *act2 = new QAction("Use Camera Stream(Default)       ",this);
	popupMenu->addAction(act2);

	openButton->setPopupMode(QToolButton::InstantPopup);
	openButton->setMenu(popupMenu);

	connect(act2, SIGNAL(triggered()), this, SLOT(useCamera()));
}


// Helper methods

void AuvMainWindow::createNewChain()
{
	//TODO: make new chains?
	filterChain = new FilterChain(filterCreator);
	filterChain->setStream(&stream);
}

// Put a button in the filterList for an existing filter
void AuvMainWindow::createNewFilterButton(int index)
{
	// Create the widgets
	const FilterCreator::StringList& filterNames = filterCreator->getFilterNames();
	QStringList filters;
	// Stupid hack to convert vector of strings to QStringList
	FilterCreator::StringList::const_iterator it;
	for (it=filterNames.begin(); it!=filterNames.end(); ++it) {
		filters << (*it).c_str();
	}
	QString btnName = QString::number(index+1);
	QString filterName = QString::fromStdString(filterChain->getChain()[index]->name);
	FilterButton *filterButton = new FilterButton(btnName, filters, filterName);

	filterButton->listItem = filterList->addItem(filterButton);

	connect(filterButton, SIGNAL(deleteFilterButton(QListWidgetItem *)),
			this, SLOT(deleteItem(QListWidgetItem *)));
	connect(filterButton, SIGNAL(deleteFilterButton(QListWidgetItem *)),
			filterList, SLOT(deleteItem(QListWidgetItem *)));
	connect(filterButton, SIGNAL(selectionChanged(const QString&)),
			this, SLOT(changeFilterType(const QString&)));
}

void AuvMainWindow::loadFile(const QString &fileName)
{
	if (!stream.useVideo(fileName.toStdString())) {
		QMessageBox::warning(this,
				tr("AUV Vision System"),
				tr("Cannot read file %1.").arg(fileName));
		return;
	}
	statusBar()->showMessage(tr("File loaded"), 2000);
}


// Slots

void AuvMainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
				tr("Open existing videos"),".",
				tr( "MPG videos (*.mpg *.mp4);;"
					"Any file (*)"));
	if (!fileName.isEmpty()) {
		loadFile(fileName);
	}
}

// Add a filter (and button) to the chain
void AuvMainWindow::appendFilterButton()
{
	// Create the filter
	filterChain->appendNewFilter();
	createNewFilterButton(filterChain->getChain().size()-1);
}

void AuvMainWindow::displaySaveSettings()
{
	popup = new SavePopup;
	popup->show();
}

void AuvMainWindow::displayHelp()
{
	HelpWidget *help = new HelpWidget;
	help->setWindowFlags(Qt::Popup);
	help->show();

	int x = window()->geometry().size().width()/2 + window()->geometry().x() - help->size().width()/2;
	int y = window()->geometry().size().height()/2 + window()->geometry().y() - help->size().height()/2;
	help->move(x, y);
}

void AuvMainWindow::listChanged()
{
	QStringList list;
	for (int i=0; i<filterList->count(); ++i) {
		QListWidgetItem *item = filterList->item(i);
		FilterButton *filterBtn = (FilterButton*)filterList->itemWidget(item);
		list << filterBtn->getName() + ": " + filterBtn->filtersComboBox->currentText();
	}
	emit filterListChanged(list);
}

void AuvMainWindow::listItemMoved(int fromRow, int toRow)
{
	filterChain->moveFilter(fromRow, toRow);
	listChanged();
	settingWidget->filterChanged(toRow);
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
	listChanged();
}

void AuvMainWindow::useCamera()
{
	stream.useCamera(0);
}

void AuvMainWindow::takeSnapshot()
{
	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	stream.writeImage((timestamp+".jpg").toStdString());
}

void AuvMainWindow::toggleRecording()
{
	if(isRecording == 0) {
		isRecording = 1;
		QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
		stream.startRecording((timestamp+".mpg").toStdString());
	} else if(isRecording == 1) {
		isRecording = 0;
		stream.stopRecording();
	}
}

void AuvMainWindow::saveChain()
{
	QString fileName = QFileDialog::getSaveFileName(this,
			tr("Save filter chain"),".",
			tr( "Filter chains (*.chain);;"
				"Any file (*)"));
	if (!fileName.isEmpty()) {
		ChainSerializer serializer;
		serializer.saveChain(fileName.toStdString(), filterChain);
	}
}

void AuvMainWindow::loadChain()
{
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open existing filter chains"),".",
			tr( "Filter chains (*.chain);;"
				"Any file (*)"));
	if (!fileName.isEmpty()) {
		ChainSerializer serializer;
		FilterChain *f = serializer.loadChain(fileName.toStdString(), filterCreator);
		if (f) {
			clearChain();

			delete filterChain;
			filterChain = f;
			f->setStream(&stream);
			settingWidget->chain = f;
			filterWidget->filterChain = f;
			filterWidget2->filterChain = f;

			for (unsigned i=0; i<filterChain->getChain().size(); ++i) {
				createNewFilterButton(i);
			}
			listChanged();
		}
	}
}

void AuvMainWindow::clearChain()
{
	for (int i=filterList->count()-1; i>=0; --i) {
		QListWidgetItem *btn = filterList->item(i);
		deleteItem(btn);
		filterList->deleteItem(btn);
	}
}
