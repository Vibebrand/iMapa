#-------------------------------------------------
#
# Project created by QtCreator 2011-05-23T12:20:09
#
#-------------------------------------------------

QT       += core gui declarative opengl sql network
TARGET = iMapa
TEMPLATE = app


SOURCES += main.cpp\
    vista/ContenedorPrincipal.cpp \
    vista/ControladorDeBurbujas.cpp \
    servicio/ServicioInformacionEstadistica.cpp \
    vista/controladorcontrollineadetiempo.cpp \
    vista/controladorpiramidepoblacional.cpp \
    modelo/PoblacionPorRangoDeEdad.cpp \
    vista/RepresentacionDeVista.cpp \
    servicio/comunicacionRed/httpdaemon.cpp \
    controlador/ControaldorVoz.cpp \
    controlador/controlmaestro.cpp \
    vista/ControladorMapa.cpp

HEADERS  += \
    vista/ContenedorPrincipal.h \
    vista/IGestionaEvento.h \
    vista/IDelegadoControladorPluginBurbujas.h \
    vista/IDelegadoGestorSeleccion.h \
    vista/IDelegadoObjetoBurbuja.h \
    vista/ControladorDeBurbujas.h \
    servicio/IServicioInformacionEstadistica.h \
    modelo/EntidadFederativa.h \
    modelo/PoblacionPorRangoDeEdad.h \
    servicio/ServicioInformacionEstadistica.h \
    vista/controladorcontrollineadetiempo.h \
    vista/controladorpiramidepoblacional.h \
    vista/IContenedorWidgets.h \
    vista/RepresentacionDeVista.h \
    vista/IWidgetInterno.h \
    servicio/comunicacionRed/iservicioelementos.h \
    servicio/comunicacionRed/httpdaemon.h \
    controlador/ControladorVoz.h \
    servicio/comunicacionRed/IDelegadoComando.h \
    controlador/controlmaestro.h \
    vista/ControladorMapa.h

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

RESOURCES += \
    vista/qml.qrc

OTHER_FILES += \
    vista/ControlLineaDeTiempo.qml \
    vista/PiramidePoblacional.qml
