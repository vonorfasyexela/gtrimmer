#include <QApplication>
#include <QDebug>
#include <gst/gst.h>
#include "window.h"
#include "gstreamer.h"

int main(int argc, char *argv[])
{
    qDebug() << "Start";
    QFont font("Ubuntu Mono", 12);
    QApplication::setFont(font);
    QApplication app(argc, argv);
    Window window;
    Gstreamer gstreamer(&argc, &argv);
    window.refresh_plugins();
    window.showMaximized();
    return app.exec();
}
