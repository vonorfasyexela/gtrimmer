QT += widgets
VPATH += src
SOURCES += main.cpp \
           window.cpp \
           gstreamer.cpp \
           mygraphicsview.cpp
HEADERS += window.h \
           gstreamer.h \
           mygraphicsview.h
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0
RESOURCES = resources.qrc
RC_ICONS = images/icons8-detective-64.ico
