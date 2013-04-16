// QListWidgetWithDrop.h
//
// Class for holding FilterButtons and drag-n-drop
// Signals:
//   - listItemMoved(int fromRow, int toRow): triggered when an item is reordered
//   - listItemAdded(): triggered when an item is added to the list
//   - listItemDeleted(): triggered when an item is deleted from the list
// Slots:
//   - deleteItem(QListWidgetItem *item): to notify the list of the deletion of an item

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
		void listItemMoved(int fromRow, int toRow);
		void listItemAdded();
		void listItemDeleted(int);
};

#endif
