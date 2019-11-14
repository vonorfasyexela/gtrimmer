#include "window.h"

Window::Window()
{
    this->setWindowTitle(WINDOW_TITLE);
    mLayout = new QVBoxLayout;
    this->setLayout(mLayout);
    mView = new QGraphicsView;
    mTree = new QTreeWidget;
    mTree->setDragEnabled(true);
    mTree->setHeaderHidden(true);
    mLayout->addWidget(mView);
    mLayout->addWidget(mTree);
    mScene = new QGraphicsScene;
    mScene->addRect(QRectF(0, 0, 100, 100));
    mView->setScene(mScene);
}

void Window::refresh_plugins()
{
    QTreeWidgetItem *sources = new QTreeWidgetItem(mTree);
    QStringList *list;
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_SRC);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *sourcesItem = new QTreeWidgetItem(sources);
        sourcesItem->setText(0, list->at(i));
    }
    sources->setText(0, "Sources (" + QString::number(list->size()) + ")");

    mTree->sortItems(0, Qt::AscendingOrder);
}

QStringList *Window::get_elements(int type)
{
    QStringList *list = new QStringList;
    GList *plugins = gst_element_factory_list_get_elements(type, GST_RANK_NONE);
    GList *l;
    for (l = plugins; l != NULL; l = l->next)
    {
        list->append(gst_object_get_name(GST_OBJECT(l->data)));
    }
    gst_plugin_feature_list_free(plugins);
    gst_plugin_feature_list_free (l);
    return list;
}