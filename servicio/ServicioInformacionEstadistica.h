#ifndef SERVICIOINFORMACIONESTADISTICA_H
#define SERVICIOINFORMACIONESTADISTICA_H
#include "IServicioInformacionEstadistica.h"

class ServicioInformacionEstadistica : public IServicioInformacionEstadistica
{
public:
    ServicioInformacionEstadistica();
    int obtenerPeriodos();
    QList<EntidadFederativa>* obtenerPeriodo(int periodo);
    qreal obtenerTotalDePoblacionPorPeriodo();
};


#endif // SERVICIOINFORMACIONESTADISTICA_H
