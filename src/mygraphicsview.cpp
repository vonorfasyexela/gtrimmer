#include <QtWidgets>

#include "mygraphicsview.h"
#include "pluginitem.h"

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "Drag entered";
    qDebug() << "Position X:" << event->pos().x() << " Y:" << event->pos().y();



    QGraphicsView::dragEnterEvent(event);
}
