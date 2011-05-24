#-------------------------------------------------
#
# Project created by QtCreator 2011-05-23T12:20:09
#
#-------------------------------------------------

QT       += core gui declarative opengl
TARGET = iMapa
TEMPLATE = app


SOURCES += main.cpp\
        ventanaprincipal.cpp \
    vista/ContenedorPrincipal.cpp

HEADERS  += ventanaprincipal.h \
    vista/ContenedorPrincipal.h

win32 {
   INCLUDEPATH += $$quote(C:/Program Files/marble/include/marble)
   LIBS += $$quote(C:/Program Files/marble/libmarblewidget.dll)
}

#qTUIO

CONFIG += precompile_header
DEFINES += OSC_HOST_LITTLE_ENDIAN

# Windows libraries for OSC Pack
win32:LIBS += "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/ws2_32.lib" \
    "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/winmm.lib"

# Main project files
HEADERS += qtuio_dll.h \
    qtuio.h
SOURCES += qtuio.cpp

# External files for the project
include( 3rdparty.pri )

#Fin qTUIO
