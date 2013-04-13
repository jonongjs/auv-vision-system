#include "QListWidgetWithDrop.h"
#include <cstdio>
#include <QDropEvent>

void QListWidgetWithDrop::dropEvent(QDropEvent *e){
	QListWidgetItem *v[count()];
	for (int i = 0; i < count(); i++)
		v[i] = item(i);
		
	QListWidget::dropEvent(e);
	
	int min = 100000000, max = -1;
	for (int i = 0; i < count(); i++){
		if (item(i) != v[i]){
			if (min == 100000000)
				min = i;
			else
				max = i;
		}
	}
	
	emit listItemSwapped(min, max);
}


void QListWidgetWithDrop::addItem(QListWidgetItem *item){
	QListWidget::addItem(item);
	emit listItemAdded();
}


void QListWidgetWithDrop::deleteItem(QListWidgetItem *item){
	int index = row(item);
	delete item;
	emit listItemDeleted(index);
}


