#ifndef GSTREAMER_H
#define GSTREAMER_H

#include <gst/gst.h>
#include <QStringList>
#include <QString>

class Gstreamer 
{
public:
    Gstreamer(int *argc, char ***argv);
    QStringList *getSourcesList();
    void addElement(QString pluginName);
private:
    GstElement *mPipeline;
};

#endif // GSTREAMER_H
