#include <QtWidgets>
#include <gst/gst.h>
#include "mygraphicsview.h"
#include "pluginitem.h"

#define WINDOW_TITLE "GTrimmer - the inspector of GStreamer"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
    void refresh_plugins();
    QStringList *get_elements(long long unsigned int type);
    void tree_item_double_clicked(QTreeWidgetItem *item, int column);
    void tree_item_clicked(QTreeWidgetItem *item, int column);
private:
    QWidget *mCentralWidget;
    QVBoxLayout *mExtLayout;
    QHBoxLayout *mIntLayout;
    QVBoxLayout *mToolLayout;
    MyGraphicsView *mView;
    QTreeWidget *mTree;
    QGraphicsScene *mScene;
    QToolBar *mToolBar;
    QTextEdit *mTextEdit;
    PluginItem *mPlugin;
    QMenuBar *mMenu;
    QMenu *mFileMenu;
    QStatusBar *mStatusBar;
};
