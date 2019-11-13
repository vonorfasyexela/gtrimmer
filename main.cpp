#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <gst/gst.h>
int main(int argc, char *argv[])
{
    qDebug() << "Start";
    QApplication app(argc, argv);
    QWidget window;

    // prepare GUI
    window.setWindowTitle("GTrimmer - the inspector of GStreamer");
    QVBoxLayout *layout = new QVBoxLayout;
    window.setLayout(layout);
    QGraphicsView *view = new QGraphicsView;
    QListWidget *list = new QListWidget;
    layout->addWidget(view);
    layout->addWidget(list);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addRect(QRectF(0, 0, 100, 100));
    view->setScene(scene);

    // init GStreamer
    gst_init(&argc, &argv);

    // get the list of plugins
    GList *plugins = gst_element_factory_list_get_elements(GST_ELEMENT_FACTORY_TYPE_SRC, GST_RANK_NONE);
    GList *l;
    for (l = plugins; l != NULL; l = l->next)
    {
        list->addItem(gst_object_get_name(GST_OBJECT(l->data)));
    }
    gst_plugin_feature_list_free(plugins);
    gst_plugin_feature_list_free (l);

    // run app
    window.showMaximized();
    return app.exec();
}
