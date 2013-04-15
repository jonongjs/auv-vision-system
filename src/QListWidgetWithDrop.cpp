#include "QListWidgetWithDrop.h"
#include <cstdio>
#include <QDropEvent>
#include "FilterButton.h"
#include <QLabel>

void QListWidgetWithDrop::dropEvent(QDropEvent *e){
	int fromRow = currentRow();
	QListWidget::dropEvent(e);
	int toRow = currentRow();

	for (int i = 0; i < count(); i++){
		FilterButton *fb = (FilterButton*) itemWidget(this->item(i));
		fb->setName(QString::number(i+1));
	}

	emit listItemMoved(fromRow, toRow);
}


QListWidgetItem* QListWidgetWithDrop::addItem(QWidget *item){
	QListWidgetItem *listitem = new QListWidgetItem();
	QListWidget::addItem(listitem);
	setItemWidget(listitem, item);
	listitem->setSizeHint(item->size());

	if (count() == 1)
		setCurrentRow(0);

	emit listItemAdded();

	return listitem;
}


void QListWidgetWithDrop::deleteItem(QListWidgetItem *item){
	int index = row(item);
	for (int i = index + 1; i < count(); i++){
		FilterButton *fb = (FilterButton*) itemWidget(this->item(i));
		fb->setName(QString::number(i));
	}
	delete item;
	
	emit listItemDeleted(index);
	emit currentRowChanged(index);
}


