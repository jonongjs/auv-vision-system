 #ifndef CUSTOMBUTTON_H
 #define CUSTOMBUTTON_H

 #include <QWidget>
 #include <QDir>

 class QComboBox;
 class QLabel;
 class QPushButton;
 class QListWidgetItem;

class CustomButton : public QWidget
 {
     Q_OBJECT

 public:
     CustomButton(QWidget *parent = 0);
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

 #endif
