INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core concurrent network

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/videos/frmvideopanel.h \
    $$PWD/videos/videowidget.h
    

SOURCES += \
    $$PWD/videos/frmvideopanel.cpp \
    $$PWD/videos/videowidget.cpp
    

FORMS += \
    $$PWD/videos/frmvideopanel.ui
