#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T18:39:30
#
#-------------------------------------------------

QT       += core gui serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSerialPortInfo
TEMPLATE = app


SOURCES += main.cpp \
    DeviceViewer.cpp \
    MainWindow.cpp \
    SerialThread.cpp \
    Console.cpp

HEADERS  += \
    DeviceViewer.h \
    MainWindow.h \
    SerialThread.h \
    GlobalData.h \
    Console.h
