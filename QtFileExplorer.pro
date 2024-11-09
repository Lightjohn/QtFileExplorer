#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T15:28:35
#
#-------------------------------------------------
config += static
QT += core gui
QT += widgets

TARGET = QtFileExplorer
TEMPLATE = app

RC_ICONS  = q.ico

SOURCES += main.cpp\
    deletetask.cpp \
    mywindows.cpp \
    fileinfo.cpp \
    imagepreview.cpp \
    keypresseater.cpp \
    refreshtask.cpp

HEADERS  += \
    deletetask.h \
    mywindows.h \
    fileinfo.h \
    imagepreview.h \
    keypresseater.h \
    refreshtask.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    ressources.qrc
