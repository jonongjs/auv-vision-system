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
#include "CustomButton.h"

//	Class declaration without loading .h files. Faster compilation.
class QHBoxLayout;
class QVBoxLayout;
class QScrollArea;
class QFrame;
class QPushButton;

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
    QWidget *rawVideoContents;
    QWidget *settingsContents;
    QPushButton *menuButton;
    CamWidget *rawCamWidget;
    CustomButton *cb;
    QListWidget *filterList;
    
    
    //	Other Variables
    CameraStream stream;
   
public slots:
void createFilterDropdown();
void moveFilterUp(QListWidgetItem *);
void moveFilterDown(QListWidgetItem *);

};

#endif
