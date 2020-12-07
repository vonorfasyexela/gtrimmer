#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
public slots:
    void zoomIn()
    {
        this->scale(1.2, 1.2);
    }
    void zoomOut()
    {
        this->scale(0.8, 0.8);
    }
private:
    bool mScroll = false;
    int mScrollStartX = 0;
    int mScrollStartY = 0;
};

#endif // MYGRAPHICSVIEW_H
