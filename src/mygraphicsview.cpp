#include "mygraphicsview.h"

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    Q_UNUSED(event);
    printf("Drag entered\n");
}
