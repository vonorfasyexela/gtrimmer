#include "gstreamer.h"

Gstreamer::Gstreamer(int *argc, char ***argv)
{
    gst_init(argc, argv);
    mPipeline = gst_pipeline_new(NULL);
};

QStringList *Gstreamer::getSourcesList()
{
    QStringList *list = new QStringList;
    // get the list of plugins
    GList *plugins = gst_element_factory_list_get_elements(GST_ELEMENT_FACTORY_TYPE_SRC, GST_RANK_NONE);
    GList *l;
    for (l = plugins; l != NULL; l = l->next)
    {
        list->append(QString(gst_object_get_name(GST_OBJECT(l->data))));
    }
    gst_plugin_feature_list_free(plugins);
    gst_plugin_feature_list_free (l);

    list->sort();
    return list;
}

void Gstreamer::addElement(QString pluginName)
{
    GstElement *element = gst_element_factory_make(qPrintable(pluginName), NULL);
    gst_bin_add(GST_BIN(mPipeline), element);
}
