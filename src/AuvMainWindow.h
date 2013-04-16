// AuvMainWindow.h
//
// Main Window for AUV software


#ifndef AUVMAINWINDOW_H
#define AUVMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QToolButton>
#include "CamWidget.h"
#include "FilterCamWidget.h"
#include "CameraStream.h"
#include "SavePopup.h"
#include "QListWidgetWithDrop.h"
#include "FilterSettingWidget.h"

//	Class declaration without loading .h files. Faster compilation.
class QHBoxLayout;
class QVBoxLayout;
class QScrollArea;
class QFrame;
class QPushButton;
class QListWidgetItem;

class FilterChain;
class FilterCreator;

class AuvMainWindow: public QMainWindow
{
	Q_OBJECT

	public:
		AuvMainWindow();
		void print();
		int videoFlag;

	private:
		//	Init methods
		void createStatusBar();
		void createMainLayout();
		void createLeftLayout();	//	used by createMainLayout
		void createMiddleLayout();
		void createRightLayout();	//	used by createMainLayout
		void createButtons();
		void createSettingsMenu();
		void createOpenMenu();
		void createFiltersMenu();
		void createNewChain();
		void loadFile(const QString &fileName);

		void createNewFilterButton(int index);


		//	Main Layout variables
		QWidget *centralWidget;
		QWidget *centralLeftWidget;
		QWidget *centralMiddleWidget;
		QWidget *centralRightWidget;
		QHBoxLayout *centralWidgetLayout;

		//	CentralLeft Layout Variables
		QScrollArea *centralLeftScrollArea;
		QVBoxLayout *centralLeftWidgetLayout;

		//	CentralMiddle Layout Variables
		QScrollArea *centralMiddleScrollArea;
		QVBoxLayout *centralMiddleWidgetLayout;
		QHBoxLayout *middleMenuContentsLayout;
		QToolButton *middleMenuButton;
		QMenu *filtersMenu;
		FilterCamWidget *filterWidget;
		FilterCamWidget *filterWidget2;

		//	CentralRight Layout Variables
		QVBoxLayout *centralRightWidgetLayout;
		QIcon *ico;
		QWidget *menuContents;
		QWidget *middleMenuContents;
		QHBoxLayout *menuContentsLayout;
		QScrollArea *rawVideoScrollArea;
		QVBoxLayout *rawVideoLayout;
		QWidget *rawVideoContents;
		QWidget *settingsContents;
		QToolButton *menuButton;
		QToolButton *recordButton;
		QPushButton *snapshotButton;
		QToolButton *openButton;
		CamWidget *rawCamWidget;
		QListWidgetWithDrop *filterList;
		FilterSettingWidget *settingWidget;
		QVBoxLayout *filterLayout;
		QScrollArea *filterSettingScrollArea;
		SavePopup *popup;
		QMenu *popupMenu;


		//	Other Variables
		CameraStream stream;
		FilterCreator *filterCreator;
		FilterChain *filterChain;


	public slots:
		void open();
		void appendFilterButton();
		void displaySaveSettings();
		void displayHelp();
		void listChanged();
		void listItemMoved(int fromRow, int toRow);
		void deleteItem(QListWidgetItem*);
		void changeFilterType(const QString& text);

		void useCamera();
		void takeSnapshot();
		void toggleRecording();

		void saveChain();
		void loadChain();
		void clearChain();

	signals:
			void filterListChanged(QStringList& filterList);
			void filterTypeChanged(int index);
};

#endif
