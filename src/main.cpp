#include <QApplication>
#include <QDebug>
#include <gst/gst.h>
#include "window.h"
#include "gstreamer.h"

int main(int argc, char *argv[])
{
    qDebug() << "Start";
    QApplication app(argc, argv);
    Window window;
    Gstreamer gstreamer(&argc, &argv);
    window.refresh_plugins();
    window.showMaximized();

    // Gstreamer gstreamer(&argc, &argv);
    // QStringList *list = gstreamer.get_sources_list();
    // for (int i = 0; i < list->size(); ++i)
    //     qDebug() << list->at(i);

    return app.exec();
}
