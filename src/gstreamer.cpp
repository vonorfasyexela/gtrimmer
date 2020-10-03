#include "gstreamer.h"

Gstreamer::Gstreamer(int *argc, char ***argv)
{
    gst_init(argc, argv);
    mPipeline = gst_pipeline_new(nullptr);
};

QStringList *Gstreamer::getSourcesList()
{
    QStringList *list = new QStringList;
    // get the list of plugins
    GList *plugins = gst_element_factory_list_get_elements(GST_ELEMENT_FACTORY_TYPE_SRC, GST_RANK_NONE);
    GList *l;
    for (l = plugins; l != nullptr; l = l->next)
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
    GstElement *element = gst_element_factory_make(qPrintable(pluginName), nullptr);
    gst_bin_add(GST_BIN(mPipeline), element);
}

QString Gstreamer::getPluginInfo(QString pluginName)
{
    QProcess inspect;
    QString command;
#ifdef Q_OS_WIN
    command = QString("gst-inspect-1.0.exe");
#else
    command = QString("gst-inspect-1.0");
#endif
    inspect.start(command, QStringList() << pluginName);
    if (!inspect.waitForStarted())
        return QString("");
    if (!inspect.waitForFinished())
        return QString("");
    QByteArray result = inspect.readAll();
    return QString(result);
}
