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
    mView->setAcceptDrops(true);

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

void Window::handleGroup(QTreeWidget *tree, PluginsGroup group) {
    QTreeWidgetItem *top_item = new QTreeWidgetItem(tree, TREE_ELEMENT_TOP);
    top_item->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
    QStringList *list;
    list = get_elements(group.type);
    for (int i = 0; i < list->size(); i++)
    {
        QTreeWidgetItem *child_item = new QTreeWidgetItem(top_item, TREE_ELEMENT_CHILD);
        child_item->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemNeverHasChildren);
        child_item->setText(0, list->at(i));
    }
    top_item->setText(0, group.name + " (" + QString::number(list->size()) + ")");
}

void Window::refresh_plugins()
{
    PluginsGroup plugin_groups[] = {
        { GST_ELEMENT_FACTORY_TYPE_SRC,            "Sources"        },
        { GST_ELEMENT_FACTORY_TYPE_SINK,           "Sinks"          },
        { GST_ELEMENT_FACTORY_TYPE_VIDEO_ENCODER,  "Video Encoders" },
        { GST_ELEMENT_FACTORY_TYPE_PAYLOADER,      "Payloaders"     },
        { GST_ELEMENT_FACTORY_TYPE_PARSER,         "Parsers"        },
        { GST_ELEMENT_FACTORY_TYPE_MUXER,          "Muxers"         },
        { GST_ELEMENT_FACTORY_TYPE_MEDIA_VIDEO,    "Video"          },
        { GST_ELEMENT_FACTORY_TYPE_MEDIA_SUBTITLE, "Subtitles"      },
        { GST_ELEMENT_FACTORY_TYPE_MEDIA_METADATA, "Metadata"       },
        { GST_ELEMENT_FACTORY_TYPE_MEDIA_IMAGE,    "Image"          },
        { GST_ELEMENT_FACTORY_TYPE_MEDIA_AUDIO,    "Audio"          },
        { GST_ELEMENT_FACTORY_TYPE_FORMATTER,      "Formatters"     },
        { GST_ELEMENT_FACTORY_TYPE_ENCODER,        "Encoders"       },
        { GST_ELEMENT_FACTORY_TYPE_DEPAYLOADER,    "Depayloaders"   },
        { GST_ELEMENT_FACTORY_TYPE_DEMUXER,        "Demuxers"       },
        { GST_ELEMENT_FACTORY_TYPE_DECODER,        "Decoders"       },
        { GST_ELEMENT_FACTORY_TYPE_AUDIO_ENCODER,  "Audio Encoders" }
    };

    size_t size = sizeof(plugin_groups) / sizeof(plugin_groups[0]);

    for (size_t i = 0; i < size; i++) {
        handleGroup(mTree, plugin_groups[i]);
    }

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
    if (item->type() == TREE_ELEMENT_CHILD) {
        QString pluginName(item->text(column));
        PluginItem *pluginItem = new PluginItem(pluginName);
        this->mScene->addItem(pluginItem);
        this->mGst->addElement(pluginName);
        this->mScene->update();
    }
}

void Window::tree_item_selection_changed()
{
    if (mTree->selectedItems().size() > 0) {
        QTreeWidgetItem *selected_item = mTree->selectedItems()[0];
        if (selected_item) {
            mTextEdit->clear();
            if (selected_item->type() == TREE_ELEMENT_CHILD) {
                mTextEdit->setText(mGst->getPluginInfo(selected_item->text(0)));
            }
        }
    }
}

void Window::showGstVersion(QString version)
{
    mGstVersionStatus->setText(version);
}
