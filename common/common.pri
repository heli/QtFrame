INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core concurrent network

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/commonutility.h \
    $$PWD/commonutility_global.h \
    $$PWD/stringutils.h
    

SOURCES += \
    $$PWD/commonutility.cpp \
    $$PWD/stringutils.cpp
    
