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
     FilterButton(QWidget *parent = 0);

     QPushButton *deleteButton;
     QListWidgetItem *listItem;
     QComboBox *filtersComboBox;
 
 private:
     QPushButton *createDeleteButton();
     QComboBox *createComboBox();
   
     QLabel *numberLabel;

signals:
    void deleteFilterDropdown(QListWidgetItem *);

private slots:
     void buttonDelete();
};

#endif//FILTERBUTTON
