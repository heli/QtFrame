INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core concurrent network

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/faceid/frmfacefeaturespanel.h \
    $$PWD/videos/frmvideopanel.h \
    $$PWD/videos/videowidget.h
    

SOURCES += \
    $$PWD/faceid/frmfacefeaturespanel.cpp \
    $$PWD/videos/frmvideopanel.cpp \
    $$PWD/videos/videowidget.cpp
    

FORMS += \
    $$PWD/faceid/frmfacefeaturespanel.ui \
    $$PWD/videos/frmvideopanel.ui
