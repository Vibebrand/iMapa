#ifndef SERVICIOINFORMACIONESTADISTICA_H
#define SERVICIOINFORMACIONESTADISTICA_H
#include "IServicioInformacionEstadistica.h"
#include <QMap>


class ServicioInformacionEstadistica : public IServicioInformacionEstadistica
{
public:
    ServicioInformacionEstadistica();
    ~ServicioInformacionEstadistica();
    int obtenerPeriodos();
    QList<EntidadFederativa>* obtenerPeriodo(int periodo);
    qreal obtenerTotalDePoblacionPorPeriodo();


private:
};


#endif // SERVICIOINFORMACIONESTADISTICA_H
