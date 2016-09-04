#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T17:28:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_modulations
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
#CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    modulations.cpp \
    radio.cpp

HEADERS  += mainwindow.h \
    modulations.h \
    radio.h

FORMS    += mainwindow.ui

LIBS += \
#/usr/lib/x86_64-linux-gnu/libboost_signals.so\
#/usr/lib/x86_64-linux-gnu/libboost_signals.so.1.54.0\
#/usr/lib/x86_64-linux-gnu/libboost_system-mt.so\
#/usr/lib/x86_64-linux-gnu/libboost_system.so\
#/usr/lib/x86_64-linux-gnu/libboost_system.so.1.54.0\
#/usr/lib/x86_64-linux-gnu/libboost_thread-mt.so\
#/usr/lib/x86_64-linux-gnu/libboost_thread.so\
#/usr/lib/x86_64-linux-gnu/libboost_thread.so.1.54.0\
#/usr/lib/x86_64-linux-gnu/libboost_timer-mt.so\
#/usr/lib/x86_64-linux-gnu/libboost_timer.so\
#/usr/local/lib/libvolk.so \
#/usr/local/lib/libvolk.so.0.0.0 \
-L/usr/local/lib -lgnuradio-audio -lgnuradio-runtime -lgnuradio-pmt -lgnuradio-blocks

LIBS+= -L/usr/local/lib -lgnuradio-analog -lgnuradio-runtime -lgnuradio-pmt -lgnuradio-audio -lgnuradio-blocks -lgnuradio-filter
LIBS+= -lgnuradio-qtgui -lgnuradio-fft -lpthread -lgnuradio-my_lte -lboost_system -lboost_signals -lboost_thread
LIBS+= -lboost_timer -lvolk -lgnuradio-digital -luhd -lgnuradio-uhd

RESOURCES += \
    icons.qrc

