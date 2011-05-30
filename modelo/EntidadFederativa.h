#ifndef ENTIDADFEDERATIVA_H
#define ENTIDADFEDERATIVA_H

#include <QString>
#include <QList>
#include "PoblacionPorRangoDeEdad.h"

class EntidadFederativa
{
public:
    QString nombre;
    int latitud;
    int longitud;
    QList<PoblacionPorRangoDeEdad> ragosDeEdad;
    int totalDePoblacion;
    int numeroPeriodo;
};

#endif // ENTIDADFEDERATIVA_H
