TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        mycurl.cpp \
        mygraphics.cpp \
        myoptions.cpp \
        myparsing.cpp

HEADERS += \
    mycurl.h \
    mygraphics.h \
    myoptions.h \
    myparsing.h

LIBS += -L/usr/lib/x86_64-linux-gnu/ -lcurl -lgd
