#include <QApplication>
#include <QDebug>
#include <gst/gst.h>
#include "gtrimmer.h"

int main(int argc, char *argv[])
{
    qDebug() << "Start";
    QApplication app(argc, argv);
    GTrimmer gTrimmer;
    gTrimmer.showMaximized();

    // // init GStreamer
    // gst_init(&argc, &argv);

    // // get the list of plugins
    // GList *plugins = gst_element_factory_list_get_elements(GST_ELEMENT_FACTORY_TYPE_SRC, GST_RANK_NONE);
    // GList *l;
    // for (l = plugins; l != NULL; l = l->next)
    // {
    //     list->addItem(gst_object_get_name(GST_OBJECT(l->data)));
    // }
    // gst_plugin_feature_list_free(plugins);
    // gst_plugin_feature_list_free (l);

    return app.exec();
}
