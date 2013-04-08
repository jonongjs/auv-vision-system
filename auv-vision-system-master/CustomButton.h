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
     QPushButton *upButton;
     QPushButton *downButton;
     QListWidgetItem *listItem;
 
 private:
     
     QPushButton *createupButton();
     QPushButton *createdownButton();
     QComboBox *createComboBox();
   
     QComboBox *filtersComboBox;
     QLabel *numberLabel;

signals:
    void moveFilterUp(QListWidgetItem *);
    void moveFilterDown(QListWidgetItem *);

private slots:
     void buttonUp();
     void buttonDown();
     
 };

 #endif
