#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <gst/gst.h>
#include "mygraphicsview.h"
#include "pluginitem.h"
#include "gstreamer.h"
#include "mygraphicsscene.h"

#define WINDOW_TITLE "GTrimmer - the inspector of GStreamer"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(int *argc, char ***argv);
    void refresh_plugins();
    QStringList *get_elements(long long unsigned int type);
    void tree_item_double_clicked(QTreeWidgetItem *item, int column);
    void tree_item_clicked(QTreeWidgetItem *item, int column);
    void showGstVersion(QString version);
private:
    Gstreamer *mGst;
    QWidget *mCentralWidget;
    QHBoxLayout *mIntLayout;
    QVBoxLayout *mToolLayout;
    MyGraphicsView *mView;
    QTreeWidget *mTree;
    MyGraphicsScene *mScene;
    QToolBar *mToolBar;
    QTextEdit *mTextEdit;
    QMenuBar *mMenu;
    QMenu *mFileMenu;
    QMenu *mViewMenu;
    QAction *mExit;
    QAction *mZoomIn;
    QAction *mZoomOut;
    QAction *mLineAction;
    QAction *mSelectAction;
    QLabel *mGstVersionStatus;
};

#endif // WINDOW_H
