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
    void tree_item_double_clicked(QTreeWidgetItem *item, int column);
private:
    QGridLayout *mLayout;
    MyGraphicsView *mView;
    QTreeWidget *mTree;
    QGraphicsScene *mScene;
    QToolBar *mToolBar;
    QTextEdit *mTextEdit;
};