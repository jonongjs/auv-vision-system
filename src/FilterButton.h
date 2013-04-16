// FilterButton.h
//
// Button representing a filter in the list of filters
// Signals:
//   - selectionChanged(const QString& text): triggered when the filter type is changed
//   - deleteFilterButton(QListWidgetItem*): triggered when the delete button is clicked

#ifndef FILTERBUTTON_H
#define FILTERBUTTON_H

#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;
class QListWidgetItem;

class FilterButton : public QWidget
{
	Q_OBJECT

	public:
		FilterButton(const QString& name, const QStringList& options, const QString& currentOption, QWidget *parent = 0);

		void setName(const QString& text);
		QString getName();

		QPushButton *deleteButton;
		QListWidgetItem *listItem;
		QComboBox *filtersComboBox;

	private:
		QPushButton *createDeleteButton();
		QComboBox *createComboBox(const QStringList&, const QString&);

		QLabel *numberLabel;

	signals:
		void selectionChanged(const QString& text);
		void deleteFilterButton(QListWidgetItem *);

	private slots:
		void buttonDelete();
};

#endif//FILTERBUTTON
