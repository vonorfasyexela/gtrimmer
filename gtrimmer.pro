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
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0
RESOURCES = resources.qrc
RC_ICONS = images/icons8-detective-64.ico
