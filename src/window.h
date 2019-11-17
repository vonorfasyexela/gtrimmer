#include <QtWidgets>
#include <gst/gst.h>
#include "mygraphicsview.h"

#define WINDOW_TITLE "GTrimmer - the inspector of GStreamer"

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
    void refresh_plugins();
    QStringList *get_elements(long long unsigned int type);
private:
    QVBoxLayout *mLayout;
    MyGraphicsView *mView;
    QTreeWidget *mTree;
    QGraphicsScene *mScene;
};