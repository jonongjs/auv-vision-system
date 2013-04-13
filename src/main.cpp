// main.cpp
//
// Main program

#include <QApplication>
#include "AuvMainWindow.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
	AuvMainWindow *mainWindow = new AuvMainWindow;
    mainWindow->show();

    return app.exec();
}
