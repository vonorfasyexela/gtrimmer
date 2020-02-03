#include <QtWidgets>

#include "mygraphicsview.h"
#include "pluginitem.h"

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    printf("Drag entered\n");
    printf("Position rX: %d, rY: %d\n", event->pos().x(), event->pos().y());

//    PluginItem *plugin = new PluginItem();
//    this->scene()->addItem(plugin);
//    plugin->setPos(event->pos().x(), event->pos().y());
}
