#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T15:28:35
#
#-------------------------------------------------
config += static
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFileExplorer
TEMPLATE = app


SOURCES += main.cpp\
    deletetask.cpp \
    mywindows.cpp \
    fileinfo.cpp \
    imagepreview.cpp \
    keypresseater.cpp

HEADERS  += \
    deletetask.h \
    mywindows.h \
    fileinfo.h \
    imagepreview.h \
    keypresseater.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    ressources.qrc
