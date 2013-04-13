// AuvMainWindow.h
//
// Main Window for AUV software


#ifndef AUVMAINWINDOW_H
#define AUVMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
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
    
private:
	//	Init methods
    void createStatusBar();
    void createMainLayout();
    void createLeftLayout();	//	used by createMainLayout
    void createMiddleLayout();
    void createRightLayout();	//	used by createMainLayout
    void createNewChain();

     
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
    
    //	CentralRight Layout Variables
    QVBoxLayout *centralRightWidgetLayout;

    QWidget *menuContents;
    QHBoxLayout *menuContentsLayout;
    QScrollArea *rawVideoScrollArea;
    QVBoxLayout *rawVideoLayout;
    QWidget *rawVideoContents;
    QWidget *settingsContents;
    QPushButton *menuButton;
    QPushButton *recordButton;
    QPushButton *snapshotButton;
    CamWidget *rawCamWidget;
    QListWidgetWithDrop *filterList;
    FilterSettingWidget *settingWidget;
    QVBoxLayout *filterLayout;
    QScrollArea *filterSettingScrollArea;
    SavePopup *popup;
    
    //	Other Variables
    CameraStream stream;
    FilterCreator *filterCreator;
    FilterChain *filterChain;
   
public slots:
	void appendFilterButton();
	void displaySaveSettings();
	void listChanged();
	void deleteItem(QListWidgetItem*);
	void changeFilterType(const QString& text);

signals:
	void filterListChanged(QStringList& filterList);
	void filterTypeChanged(int index);
};

#endif
