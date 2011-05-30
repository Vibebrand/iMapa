#include "servicio/ServicioInformacionEstadistica.h"

ServicioInformacionEstadistica::ServicioInformacionEstadistica(){}

int ServicioInformacionEstadistica::obtenerPeriodos()
{
    return 1;
}

QList<EntidadFederativa>* ServicioInformacionEstadistica::obtenerPeriodo(int periodo)
{
    return new QList<EntidadFederativa>();
}

qreal ServicioInformacionEstadistica::obtenerTotalDePoblacionPorPeriodo()
{
    return 0.0;
}

