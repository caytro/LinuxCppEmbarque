TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../AIrQualityWAtch/myoptions.cpp \
        ../AIrQualityWAtch/myparsing.cpp \
        ../AIrQualityWAtch/myregex.cpp \
        main.cpp

HEADERS += \
    ../AIrQualityWAtch/myoptions.h \
    ../AIrQualityWAtch/myparsing.h \
    ../AIrQualityWAtch/myregex.h

