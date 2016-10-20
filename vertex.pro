#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T18:49:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vertex
TEMPLATE = app


SOURCES += main.cpp\
        vertexhelp.cpp \
    imagelabel.cpp

HEADERS  += vertexhelp.h \
    imagelabel.h

RESOURCES += \
    image/image.qrc

OTHER_FILES += \
    kls.rc

RC_FILE = \
  kls.rc
