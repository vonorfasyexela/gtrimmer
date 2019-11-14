#include <gst/gst.h>
#include <QStringList>
#include <QString>

class Gstreamer 
{
public:
    Gstreamer(int *argc, char ***argv);
    QStringList *get_sources_list();
    // void init();
};