#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
public slots:
    void zoomIn()
    {
        this->scale(1.2, 1.2);
    }
    void zoomOut()
    {
        this->scale(0.8, 0.8);
    }
};

#endif // MYGRAPHICSVIEW_H
