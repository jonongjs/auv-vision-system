#ifndef QLISTWIDGETWITHDROP_H
#define QLISTWIDGETWITHDROP_H

#include <QListWidget>
#include <QListWidgetItem>

class QListWidgetWithDrop : public QListWidget
{
     Q_OBJECT

public:
	void dropEvent(QDropEvent *);
	QListWidgetItem* addItem(QWidget *item);
	
public slots:
	void deleteItem(QListWidgetItem *item);
	
signals:
	void listItemSwapped(int, int);
	void listItemAdded();
	void listItemDeleted(int);
};


#endif
