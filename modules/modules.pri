INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core concurrent network
QT += multimedia multimediawidgets

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/faceid/camerawidget.h \
    $$PWD/faceid/frmfacefeaturespanel.h \
    $$PWD/videos/frmvideopanel.h \
    $$PWD/videos/videoplayer.h \
    $$PWD/videos/videowidget.h
    

SOURCES += \
    $$PWD/faceid/camerawidget.cpp \
    $$PWD/faceid/frmfacefeaturespanel.cpp \
    $$PWD/videos/frmvideopanel.cpp \
    $$PWD/videos/videoplayer.cpp \
    $$PWD/videos/videowidget.cpp
    

FORMS += \
    $$PWD/faceid/camerawidget.ui \
    $$PWD/faceid/frmfacefeaturespanel.ui \
    $$PWD/videos/frmvideopanel.ui \
    $$PWD/videos/videoplayer.ui
