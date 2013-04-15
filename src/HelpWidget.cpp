// HelpWidget.cpp

#include "HelpWidget.h"
#include <QPushButton>
using namespace std;

HelpWidget::HelpWidget()
{
	layout = new QVBoxLayout;
	this->setLayout(layout);
	area = new QScrollArea;
	area->setWidget(this);
	createText();
}

void HelpWidget::createText(){
	QLabel *label = new QLabel("Shortcuts");
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;font:bold;margin-top:18px;}");
	layout->addWidget(label);
	layout->addWidget(createLabel(QString("Ctrl+N: Add new filters ")));
	layout->addWidget(createLabel(QString("Ctrl+O: Open Video")));
	layout->addWidget(createLabel(QString("Ctrl+M: Additional Menu")));
	layout->addWidget(createLabel(QString("Alt+S: Snapshot")));
	layout->addWidget(createLabel(QString("Alt+R: Record Video")));
	
	QPushButton *button = new QPushButton;
	button->setText("Ok");
	connect(button, SIGNAL(clicked()), this, SLOT(end()));
	layout->addWidget(button);
}

QLabel* HelpWidget::createLabel(QString str){
	QLabel *label = new QLabel(str);
	label->setStyleSheet("QLabel{color:#8E5316;font-size:15px;margin-top:18px;}");
	return label;
}

void HelpWidget::end(){
	delete this;
}
