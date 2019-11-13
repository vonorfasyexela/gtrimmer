#include <QtWidgets>

#define WINDOW_TITLE "GTrimmer - the inspector of GStreamer"

class GTrimmer : public QWidget
{
    Q_OBJECT
public:
    GTrimmer();
private:
    QVBoxLayout *mLayout;
    QGraphicsView *mView;
    QListWidget *mList;
    QGraphicsScene *mScene;
};