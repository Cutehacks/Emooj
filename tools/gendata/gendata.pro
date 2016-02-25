TEMPLATE = app
TARGET = gendata
INCLUDEPATH += .

SOURCES += main.cpp

CONFIG += c++11

DEFINES += SRCDIR=\\\"$$clean_path($$PWD/../..)\\\"

macx:CONFIG -= app_bundle
win32:CONFIG += console
