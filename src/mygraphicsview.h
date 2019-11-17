#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
};