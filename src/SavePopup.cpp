#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPixmap>

#include <QFileDialog>
#include "SavePopup.h"

SavePopup:: SavePopup(QWidget *parent): QWidget(parent)
{
	setWindowTitle(tr("Additional Options"));
	this->setGeometry(QRect(200, 200, 600, 100));
	saveLabel = new QLabel(tr("Save Destination")); 
	directoryComboBox = createComboBox(QDir::currentPath());
	browseButton = createButton(tr("&Browse..."), SLOT(browse()));
	okButton = createButton(tr("&OK"), SLOT(close()));
	okButton->setDefault(true);
	cancelButton = createButton(tr("&Cancel"), SLOT(close()));
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
	mainLayout->addWidget(saveLabel, 0, 0);
	mainLayout->addWidget(directoryComboBox, 0, 1);
	mainLayout->addWidget(browseButton, 0, 2);
	mainLayout->addWidget(okButton,1,2);
	setLayout(mainLayout);
}


QPushButton *SavePopup::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}

QComboBox *SavePopup::createComboBox(const QString &text)
{
	QComboBox *comboBox = new QComboBox;
	comboBox->setEditable(true);
	comboBox->addItem(text);
	comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	return comboBox;
}

void SavePopup::browse()
{
	QString directory = QFileDialog::getExistingDirectory(this,tr("Choose Folder"), QDir::currentPath());

	if (!directory.isEmpty()) 
	{
		if (directoryComboBox->findText(directory) == -1)
			directoryComboBox->addItem(directory);
		directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
	}
}
