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

// Class declaration without loading .h files. Faster compilation.
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

	private:
		// Widget creation methods
		void createStatusBar();

		void createMainLayout();
		void createLeftLayout();	// used by createMainLayout
		void createMiddleLayout();
		void createRightLayout();	// used by createMainLayout

		void createButtons();
		void createSettingsMenu();
		void createFiltersMenu();
		void createOpenMenu();

		// Helper methods
		void createNewChain();
		void createNewFilterButton(int index);
		void loadFile(const QString &fileName);

		// Main Layout variables
		QWidget *centralWidget;
		QWidget *centralLeftWidget;
		QWidget *centralMiddleWidget;
		QWidget *centralRightWidget;
		QHBoxLayout *centralWidgetLayout;

		// CentralLeft Layout Variables
		QScrollArea *centralLeftScrollArea;
		QVBoxLayout *centralLeftWidgetLayout;
		FilterCamWidget *filterWidget;
		FilterCamWidget *filterWidget2;

		// CentralMiddle Layout Variables
		QScrollArea *centralMiddleScrollArea;
		QVBoxLayout *centralMiddleWidgetLayout;
		QHBoxLayout *middleMenuContentsLayout;
		QToolButton *middleMenuButton;
		QWidget *middleMenuContents;
		QMenu *filtersMenu;

		// CentralRight Layout Variables
		QWidget *menuContents;
		QHBoxLayout *menuContentsLayout;
		QVBoxLayout *centralRightWidgetLayout;
		QVBoxLayout *rawVideoLayout;
		QWidget *rawVideoContents;
		CamWidget *rawCamWidget;
		FilterSettingWidget *settingWidget;

		QToolButton *menuButton;
		QToolButton *recordButton;
		QPushButton *snapshotButton;
		QToolButton *openButton;

		QListWidgetWithDrop *filterList;
		SavePopup *popup;

		// Other Variables
		CameraStream stream;
		FilterCreator *filterCreator;
		FilterChain *filterChain;

		int isRecording;

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
