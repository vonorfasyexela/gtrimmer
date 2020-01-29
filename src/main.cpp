#include <QApplication>
#include <QDebug>
#include <gst/gst.h>
#include "window.h"
#include "gstreamer.h"

int main(int argc, char *argv[])
{
    qDebug() << "Start";
    QApplication app(argc, argv);
    Gstreamer gstreamer(&argc, &argv);
    Window window;
    window.refresh_plugins();

    // fix issue with short menubar
    window.setGeometry(app.screens()[0]->geometry());
    window.showMaximized();

    return app.exec();
}
