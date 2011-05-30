#ifndef ISERVICIOINFORMACIONESTADISTICA_H
#define ISERVICIOINFORMACIONESTADISTICA_H

#include "modelo/EntidadFederativa.h"
#include "QList"
class IServicioInformacionEstadistica
{
public:
    virtual int obtenerPeriodos();
    virtual QList<EntidadFederativa>* obtenerPeriodo(int periodo)=0;
    virtual qreal obtenerTotalDePoblacionPorPeriodo();
};

#endif // ISERVICIOINFORMACIONESTADISTICA_H
