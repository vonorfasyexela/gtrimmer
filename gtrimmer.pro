QT += widgets
VPATH += src
SOURCES += main.cpp \
           window.cpp \
           gstreamer.cpp \
           mygraphicsview.cpp \
    src/pluginitem.cpp
HEADERS += window.h \
           gstreamer.h \
           mygraphicsview.h \
    src/pluginitem.h
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += gstreamer-1.0
}
win32 {
    GstreamerDir=$$(GSTREAMER_1_0_ROOT_X86_64)

    INCLUDEPATH = $${GstreamerDir}/include/gstreamer-1.0
    INCLUDEPATH += $${GstreamerDir}/include/glib-2.0
    INCLUDEPATH += $${GstreamerDir}/lib/glib-2.0/include
    INCLUDEPATH += $${GstreamerDir}/lib/gstreamer-1.0/include

    LIBS = $${GstreamerDir}/lib/gstreamer-1.0.lib
    LIBS += $${GstreamerDir}/lib/*.lib
}
RESOURCES = resources.qrc
RC_ICONS = images/icons8-detective-64.ico
