#include "window.h"

Window::Window(int *argc, char ***argv)
{
    // Setup main window
    this->setWindowTitle(WINDOW_TITLE);
    this->setWindowIcon(QIcon(":/icon"));
    mCentralWidget = new QWidget;
    this->setCentralWidget(mCentralWidget);

    // Setup actions
    mExit = new QAction("Exit", this);
    mExit->setIcon(QIcon(":/exit"));
    mZoomIn = new QAction("Zoom In", this);
    mZoomIn->setIcon(QIcon(":/zoomin"));
    mZoomOut = new QAction("Zoom Out", this);
    mZoomOut->setIcon(QIcon(":/zoomout"));
    mLineAction = new QAction("Line Mode", this);
    mLineAction->setIcon(QIcon(":/pencil"));
    mLineAction->setCheckable(true);
    mSelectAction = new QAction("Select Mode", this);
    mSelectAction->setIcon(QIcon(":/cursor"));
    mSelectAction->setCheckable(true);
    mSelectAction->setChecked(true);

    mViewActions = new QActionGroup(this);
    mViewActions->setExclusive(true);
    mViewActions->addAction(mSelectAction);
    mViewActions->addAction(mLineAction);

    // Setup menu
    mMenu = this->menuBar();
    mFileMenu = new QMenu("File");
    mFileMenu->addAction(mExit);
    mViewMenu = new QMenu("View");
    mViewMenu->addAction(mZoomIn);
    mViewMenu->addAction(mZoomOut);
    mMenu->addMenu(mFileMenu);
    mMenu->addMenu(mViewMenu);

    // Setup toolbar
    mToolBar = new QToolBar;
    mToolBar->setMovable(false);
    mToolBar->addAction(mZoomIn);
    mToolBar->addAction(mZoomOut);
    mToolBar->addAction(mSelectAction);
    mToolBar->addAction(mLineAction);
    this->addToolBar(mToolBar);

    // Setup statusbar
    mGstVersionStatus = new QLabel;
    this->statusBar()->addPermanentWidget(mGstVersionStatus);
    this->statusBar()->show();

    // Setup tree for the plugins
    mTree = new QTreeWidget;
    mTree->setDragEnabled(true);
    mTree->setHeaderHidden(true);

    // Setup text editor
    mTextEdit = new QTextEdit;
    mTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    mTextEdit->setReadOnly(true);
    mTextEdit->setFontFamily("Courier");
    mTextEdit->setFontPointSize(10);

    // Setup graphics view
    mView = new MyGraphicsView;
    mScene = new MyGraphicsScene;
    mView->setScene(mScene);

    // Setup layout
    mIntLayout = new QHBoxLayout;
    mToolLayout = new QVBoxLayout;

    this->centralWidget()->setLayout(mIntLayout);

    mIntLayout->addWidget(mView);
    mIntLayout->addLayout(mToolLayout);

    mToolLayout->addWidget(mTree);
    mToolLayout->addWidget(mTextEdit);

    // Connect signals and callbacks
    QObject::connect(mTree, &QTreeWidget::itemSelectionChanged, this, &Window::tree_item_selection_changed);
    QObject::connect(mTree, &QTreeWidget::itemDoubleClicked, this, &Window::tree_item_double_clicked);
    QObject::connect(mZoomIn, &QAction::triggered, mView, &MyGraphicsView::zoomIn);
    QObject::connect(mZoomOut, &QAction::triggered, mView, &MyGraphicsView::zoomOut);
    QObject::connect(mExit, &QAction::triggered, this, &Window::close);

    // Setup GStreamer
    mGst = new Gstreamer(argc, argv);
}

void Window::refresh_plugins()
{
    // Sources
    QTreeWidgetItem *sources = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    QStringList *list;
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_SRC);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *sourcesItem = new QTreeWidgetItem(sources, TREE_ELEMENT_CHILD);
        sourcesItem->setText(0, list->at(i));
    }
    sources->setText(0, "Sources (" + QString::number(list->size()) + ")");

    // Sinks
    QTreeWidgetItem *sinks = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_SINK);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *sinksItem = new QTreeWidgetItem(sinks, TREE_ELEMENT_CHILD);
        sinksItem->setText(0, list->at(i));
    }
    sinks->setText(0, "Sinks (" + QString::number(list->size()) + ")");

    // Video Encoders
    QTreeWidgetItem *videoenc = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_VIDEO_ENCODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *videoencItem = new QTreeWidgetItem(videoenc, TREE_ELEMENT_CHILD);
        videoencItem->setText(0, list->at(i));
    }
    videoenc->setText(0, "Video Encoders (" + QString::number(list->size()) + ")");

    // Payloaders
    QTreeWidgetItem *payloaders = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_PAYLOADER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *payloadersItem = new QTreeWidgetItem(payloaders, TREE_ELEMENT_CHILD);
        payloadersItem->setText(0, list->at(i));
    }
    payloaders->setText(0, "Payloaders (" + QString::number(list->size()) + ")");

    // Parsers
    QTreeWidgetItem *parsers = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_PARSER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *parsersItem = new QTreeWidgetItem(parsers, TREE_ELEMENT_CHILD);
        parsersItem->setText(0, list->at(i));
    }
    parsers->setText(0, "Parsers (" + QString::number(list->size()) + ")");

    // Muxers
    QTreeWidgetItem *muxers = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MUXER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *muxersItem = new QTreeWidgetItem(muxers, TREE_ELEMENT_CHILD);
        muxersItem->setText(0, list->at(i));
    }
    muxers->setText(0, "Muxers (" + QString::number(list->size()) + ")");

    // Video
    QTreeWidgetItem *videos = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_VIDEO);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *videosItem = new QTreeWidgetItem(videos, TREE_ELEMENT_CHILD);
        videosItem->setText(0, list->at(i));
    }
    videos->setText(0, "Video (" + QString::number(list->size()) + ")");

    // Subtitles
    QTreeWidgetItem *subtitles = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_SUBTITLE);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *subtitlesItem = new QTreeWidgetItem(subtitles, TREE_ELEMENT_CHILD);
        subtitlesItem->setText(0, list->at(i));
    }
    subtitles->setText(0, "Subtitles (" + QString::number(list->size()) + ")");

    // Metadata
    QTreeWidgetItem *metadata = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_METADATA);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *metadataItem = new QTreeWidgetItem(metadata, TREE_ELEMENT_CHILD);
        metadataItem->setText(0, list->at(i));
    }
    metadata->setText(0, "Metadata (" + QString::number(list->size()) + ")");

    // Image
    QTreeWidgetItem *images = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_IMAGE);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *imagesItem = new QTreeWidgetItem(images, TREE_ELEMENT_CHILD);
        imagesItem->setText(0, list->at(i));
    }
    images->setText(0, "Image (" + QString::number(list->size()) + ")");

    // Audio
    QTreeWidgetItem *audios = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_MEDIA_AUDIO);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *audiosItem = new QTreeWidgetItem(audios, TREE_ELEMENT_CHILD);
        audiosItem->setText(0, list->at(i));
    }
    audios->setText(0, "Audio (" + QString::number(list->size()) + ")");

    // Formatters
    QTreeWidgetItem *formatters = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_FORMATTER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *formattersItem = new QTreeWidgetItem(formatters, TREE_ELEMENT_CHILD);
        formattersItem->setText(0, list->at(i));
    }
    formatters->setText(0, "Formatters (" + QString::number(list->size()) + ")");

    // Encoders
    QTreeWidgetItem *encoders = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_ENCODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *encodersItem = new QTreeWidgetItem(encoders, TREE_ELEMENT_CHILD);
        encodersItem->setText(0, list->at(i));
    }
    encoders->setText(0, "Encoders (" + QString::number(list->size()) + ")");

    // Depayloaders
    QTreeWidgetItem *depayloaders = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_DEPAYLOADER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *depayloadersItem = new QTreeWidgetItem(depayloaders, TREE_ELEMENT_CHILD);
        depayloadersItem->setText(0, list->at(i));
    }
    depayloaders->setText(0, "Depayloaders (" + QString::number(list->size()) + ")");    

    // Demuxers
    QTreeWidgetItem *demuxers = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_DEMUXER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *demuxersItem = new QTreeWidgetItem(demuxers, TREE_ELEMENT_CHILD);
        demuxersItem->setText(0, list->at(i));
    }
    demuxers->setText(0, "Demuxers (" + QString::number(list->size()) + ")");   

    // Decoders
    QTreeWidgetItem *decoders = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_DECODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *decodersItem = new QTreeWidgetItem(decoders, TREE_ELEMENT_CHILD);
        decodersItem->setText(0, list->at(i));
    }
    decoders->setText(0, "Decoders (" + QString::number(list->size()) + ")");   

    // Audio Encoders
    QTreeWidgetItem *audioenc = new QTreeWidgetItem(mTree, TREE_ELEMENT_TOP);
    list = get_elements(GST_ELEMENT_FACTORY_TYPE_AUDIO_ENCODER);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *audioencItem = new QTreeWidgetItem(audioenc, TREE_ELEMENT_CHILD);
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
    for (l = plugins; l != nullptr; l = l->next)
    {
        list->append(gst_object_get_name(GST_OBJECT(l->data)));
    }
    gst_plugin_feature_list_free(plugins);
    gst_plugin_feature_list_free (l);
    return list;
}

void Window::tree_item_double_clicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item)
    Q_UNUSED(column)
    qDebug() << "Double clicked";
    QString pluginName(item->text(column));
    PluginItem *pluginItem = new PluginItem(pluginName);
    this->mScene->addItem(pluginItem);
    this->mGst->addElement(pluginName);
    this->mScene->update();
}

void Window::tree_item_selection_changed()
{
    QTreeWidgetItem *selected_item = mTree->selectedItems()[0];
    if (selected_item) {
        mTextEdit->clear();
        if (selected_item->type() == TREE_ELEMENT_CHILD) {
            mTextEdit->setText(mGst->getPluginInfo(selected_item->text(0)));
        }
    }
}

void Window::showGstVersion(QString version)
{
    mGstVersionStatus->setText(version);
}
