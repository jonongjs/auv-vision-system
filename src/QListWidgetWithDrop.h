#ifndef QLISTWIDGETWITHDROP_H
#define QLISTWIDGETWITHDROP_H

#include <QListWidget>
#include <QListWidgetItem>

class QListWidget;

class QListWidgetWithDrop : public QListWidget
{
     Q_OBJECT

public:
	void dropEvent(QDropEvent *);
	void addItem(QListWidgetItem *item);
	
public slots:
	void deleteItem(QListWidgetItem *item);
	
signals:
	void listItemSwapped(int, int);
	void listItemAdded();
	void listItemDeleted(int);
};


#endif
