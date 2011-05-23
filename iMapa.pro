#-------------------------------------------------
#
# Project created by QtCreator 2011-05-23T12:20:09
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = iMapa
TEMPLATE = app


SOURCES += main.cpp\
        ventanaprincipal.cpp

HEADERS  += ventanaprincipal.h

win32 {
   INCLUDEPATH += $$quote(C:/Program Files/marble/include/marble)
   LIBS += $$quote(C:/Program Files/marble/libmarblewidget.dll)
}
