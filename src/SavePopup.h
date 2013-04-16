#ifndef SAVEPOPUP_H
#define SAVEPOPUP_H

#include <QWidget>
#include <QDir>

class QComboBox;
class QLabel;
class QPushButton;
class QListWidgetItem;

class SavePopup : public QWidget
{
	Q_OBJECT

	public:
		SavePopup(QWidget *parent = 0);
		QPushButton *createButton(const QString &text, const char *member);
		QComboBox *createComboBox(const QString &text = QString());


	private:

		QLabel *saveLabel;
		QPushButton *browseButton;
		QPushButton *okButton;
		QPushButton *cancelButton;
		QComboBox *directoryComboBox;
		QDir currentDir;

	private slots:
		void browse();
};

#endif
