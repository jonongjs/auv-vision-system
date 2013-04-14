#include "QListWidgetWithDrop.h"
#include <cstdio>
#include <QDropEvent>

void QListWidgetWithDrop::dropEvent(QDropEvent *e){
	int fromRow = currentRow();
	QListWidget::dropEvent(e);
	int toRow = currentRow();

	emit listItemMoved(fromRow, toRow);
}


QListWidgetItem* QListWidgetWithDrop::addItem(QWidget *item){
	QListWidgetItem *listitem = new QListWidgetItem();
	QListWidget::addItem(listitem);
	if (count() == 1)
		setCurrentRow(0);
	setItemWidget(listitem, item);
	listitem->setSizeHint(item->size());

	emit listItemAdded();

	return listitem;
}


void QListWidgetWithDrop::deleteItem(QListWidgetItem *item){
	int index = row(item);	
	delete item;
	emit listItemDeleted(index);	
}


