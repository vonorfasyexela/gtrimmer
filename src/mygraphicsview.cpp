#include <QtWidgets>

#include "mygraphicsview.h"
#include "pluginitem.h"

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "Drag entered";
    qDebug() << "Position X:" << event->pos().x() << " Y:" << event->pos().y();



    QGraphicsView::dragEnterEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        setCursor(Qt::ClosedHandCursor);
        mScroll = true;
        mScrollStartX = event->x();
        mScrollStartY = event->y();
    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (mScroll) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - mScrollStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - mScrollStartY));
        mScrollStartX = event->x();
        mScrollStartY = event->y();
    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        setCursor(Qt::ArrowCursor);
        mScroll = false;
    }
}
