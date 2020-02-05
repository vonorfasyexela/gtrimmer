#include <QApplication>
#include <QDebug>
#include <gst/gst.h>
#include "window.h"
#include "gstreamer.h"

int main(int argc, char *argv[])
{
    // on some platforms resources are placed as static library
    // and this string is required there
    Q_INIT_RESOURCE(resources);

    qDebug() << "Start";
    QApplication app(argc, argv);
//    Gstreamer gstreamer(&argc, &argv);
    Window window(&argc, &argv);
    window.refresh_plugins();
    window.showGstVersion(gst_version_string());

    // fix issue with short menubar
    window.setGeometry(app.screens()[0]->geometry());
    window.showMaximized();

    return app.exec();
}
