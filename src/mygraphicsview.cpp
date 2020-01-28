#include "mygraphicsview.h"

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    (void)event;
    printf("Drag entered\n");
}
