#-------------------------------------------------
#
# Project created by QtCreator 2020-09-17T11:23:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qframe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    layouts/framelesswidget.cpp \
    layouts/navbarleftwidget.cpp \
    layouts/navtreeleftwidget.cpp

HEADERS += \
        mainwindow.h \
    layouts/framelesswidget.h \
    layouts/navbarleftwidget.h \
    layouts/navtreeleftwidget.h

FORMS += \
        mainwindow.ui \
    layouts/framelesswidget.ui \
    layouts/navbarleftwidget.ui \
    layouts/navtreeleftwidget.ui

RESOURCES += \
    resource/resouce.qrc \
    resource/qss.qrc



RC_FILE += layouts/images/window.rc

RESOURCES += layouts/images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
