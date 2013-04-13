// FilterButton.h
//
// Button representing a filter in the list of filters

#ifndef FILTERBUTTON_H
#define FILTERBUTTON_H

#include <QWidget>
#include <QDir>

class QComboBox;
class QLabel;
class QPushButton;
class QListWidgetItem;

class FilterButton : public QWidget
{
     Q_OBJECT

 public:
     FilterButton(const QString& name, const QStringList& options, QWidget *parent = 0);

     QPushButton *deleteButton;
     QListWidgetItem *listItem;
     QComboBox *filtersComboBox;

	 QString getName();
 
 private:
     QPushButton *createDeleteButton();
     QComboBox *createComboBox(const QStringList&);
   
     QLabel *numberLabel;

signals:
    void deleteFilterButton(QListWidgetItem *);

private slots:
     void buttonDelete();
};

#endif//FILTERBUTTON
