#ifndef ENTIDADFEDERATIVA_H
#define ENTIDADFEDERATIVA_H

#include <QString>
#include <QList>
#include "PoblacionPorRangoDeEdad.h"

class EntidadFederativa
{
public:
    QString nombre;
    double latitud;
    double longitud;
    double nHombresPorEntidad;
    double nMujeresPorEntidad;

    QList<PoblacionPorRangoDeEdad *> ragosDeEdad;

    double totalDePoblacion;

    int numeroPeriodo;
    double porcentajeNacionalDePoblacion;
};

#endif // ENTIDADFEDERATIVA_H
