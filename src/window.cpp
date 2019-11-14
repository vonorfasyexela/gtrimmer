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
    // Sources
    QTreeWidgetItem *sources = new QTreeWidgetItem(mTree);
    QStringList *list;
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_SRC);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *sourcesItem = new QTreeWidgetItem(sources);
        sourcesItem->setText(0, list->at(i));
    }
    sources->setText(0, "Sources (" + QString::number(list->size()) + ")");

    // Sinks
    QTreeWidgetItem *sinks = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_SINK);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *sinksItem = new QTreeWidgetItem(sinks);
        sinksItem->setText(0, list->at(i));
    }
    sinks->setText(0, "Sinks (" + QString::number(list->size()) + ")");

    // Video Encoders
    QTreeWidgetItem *videoenc = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_VIDEO_ENCODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *videoencItem = new QTreeWidgetItem(videoenc);
        videoencItem->setText(0, list->at(i));
    }
    videoenc->setText(0, "Video Encoders (" + QString::number(list->size()) + ")");

    // Payloaders
    QTreeWidgetItem *payloaders = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_PAYLOADER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *payloadersItem = new QTreeWidgetItem(payloaders);
        payloadersItem->setText(0, list->at(i));
    }
    payloaders->setText(0, "Payloaders (" + QString::number(list->size()) + ")");

    // Parsers
    QTreeWidgetItem *parsers = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_PARSER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *parsersItem = new QTreeWidgetItem(parsers);
        parsersItem->setText(0, list->at(i));
    }
    parsers->setText(0, "Parsers (" + QString::number(list->size()) + ")");

    // Muxers
    QTreeWidgetItem *muxers = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MUXER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *muxersItem = new QTreeWidgetItem(muxers);
        muxersItem->setText(0, list->at(i));
    }
    muxers->setText(0, "Muxers (" + QString::number(list->size()) + ")");

    // Video
    QTreeWidgetItem *videos = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_VIDEO);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *videosItem = new QTreeWidgetItem(videos);
        videosItem->setText(0, list->at(i));
    }
    videos->setText(0, "Video (" + QString::number(list->size()) + ")");

    // Subtitles
    QTreeWidgetItem *subtitles = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_SUBTITLE);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *subtitlesItem = new QTreeWidgetItem(subtitles);
        subtitlesItem->setText(0, list->at(i));
    }
    subtitles->setText(0, "Subtitles (" + QString::number(list->size()) + ")");

    // Metadata
    QTreeWidgetItem *metadata = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_METADATA);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *metadataItem = new QTreeWidgetItem(metadata);
        metadataItem->setText(0, list->at(i));
    }
    metadata->setText(0, "Metadata (" + QString::number(list->size()) + ")");

    // Image
    QTreeWidgetItem *images = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_IMAGE);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *imagesItem = new QTreeWidgetItem(images);
        imagesItem->setText(0, list->at(i));
    }
    images->setText(0, "Image (" + QString::number(list->size()) + ")");

    // Audio
    QTreeWidgetItem *audios = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_AUDIO);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *audiosItem = new QTreeWidgetItem(audios);
        audiosItem->setText(0, list->at(i));
    }
    audios->setText(0, "Audio (" + QString::number(list->size()) + ")");

    // Formatters
    QTreeWidgetItem *formatters = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_FORMATTER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *formattersItem = new QTreeWidgetItem(formatters);
        formattersItem->setText(0, list->at(i));
    }
    formatters->setText(0, "Formatters (" + QString::number(list->size()) + ")");

    // Encoders
    QTreeWidgetItem *encoders = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_ENCODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *encodersItem = new QTreeWidgetItem(encoders);
        encodersItem->setText(0, list->at(i));
    }
    encoders->setText(0, "Encoders (" + QString::number(list->size()) + ")");

    // Depayloaders
    QTreeWidgetItem *depayloaders = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_DEPAYLOADER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *depayloadersItem = new QTreeWidgetItem(depayloaders);
        depayloadersItem->setText(0, list->at(i));
    }
    depayloaders->setText(0, "Depayloaders (" + QString::number(list->size()) + ")");    

    // Demuxers
    QTreeWidgetItem *demuxers = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_DEMUXER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *demuxersItem = new QTreeWidgetItem(demuxers);
        demuxersItem->setText(0, list->at(i));
    }
    demuxers->setText(0, "Demuxers (" + QString::number(list->size()) + ")");   

    // Decoders
    QTreeWidgetItem *decoders = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_DECODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *decodersItem = new QTreeWidgetItem(decoders);
        decodersItem->setText(0, list->at(i));
    }
    decoders->setText(0, "Decoders (" + QString::number(list->size()) + ")");   

    // Audio Encoders
    QTreeWidgetItem *audioenc = new QTreeWidgetItem(mTree);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_AUDIO_ENCODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *audioencItem = new QTreeWidgetItem(audioenc);
        audioencItem->setText(0, list->at(i));
    }
    audioenc->setText(0, "Audio Encoders (" + QString::number(list->size()) + ")");   

    mTree->sortItems(0, Qt::AscendingOrder);
}

QStringList *Window::get_elements(long long unsigned int type)
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