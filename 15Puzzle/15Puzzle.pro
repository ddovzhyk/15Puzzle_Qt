QT += qml quick widgets core

CONFIG += c++11

TARGET = 15Puzzle
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    logic.cpp

HEADERS += \
    logic.h

DISTFILES += \
    main.qml
