#include "gtrimmer.h"

GTrimmer::GTrimmer()
{
    this->setWindowTitle(WINDOW_TITLE);
    mLayout = new QVBoxLayout;
    this->setLayout(mLayout);
    mView = new QGraphicsView;
    mList = new QListWidget;
    mList->setDragEnabled(true);
    mLayout->addWidget(mView);
    mLayout->addWidget(mList);
    mScene = new QGraphicsScene;
    mScene->addRect(QRectF(0, 0, 100, 100));
    mView->setScene(mScene);
}