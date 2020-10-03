#ifndef GSTREAMER_H
#define GSTREAMER_H

#include <gst/gst.h>
#include <QStringList>
#include <QString>
#include <QProcess>

class Gstreamer 
{
public:
    Gstreamer(int *argc, char ***argv);
    QStringList *getSourcesList();
    void addElement(QString pluginName);
    QString getPluginInfo(QString pluginName);
private:
    GstElement *mPipeline;
};

#endif // GSTREAMER_H
