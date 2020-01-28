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
    QDesktopWidget dw;
    window.setGeometry(0, 0, dw.width(), dw.height());
    window.showMaximized();

    return app.exec();
}
