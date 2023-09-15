TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        mycurl.cpp \
        myparsing.cpp

HEADERS += \
    mycurl.h \
    myparsing.h

LIBS += -L/usr/lib/x86_64-linux-gnu/ -lcurl
