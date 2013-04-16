// HelpWidget.h

#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

class HelpWidget: public QWidget
{
	Q_OBJECT

	public:
		HelpWidget();
		void createText();
		QLabel* createLabel(QString string);

	public slots:
		void end();

	private:
		QScrollArea *area;
		QVBoxLayout *layout;

};

#endif
