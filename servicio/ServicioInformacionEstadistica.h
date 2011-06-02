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
    const QList<EntidadFederativa*>* obtenerPeriodo(int periodo);
    double obtenerTotalDePoblacionPorPeriodo();


private:
        QMap<int, EntidadFederativa*> * obtenerElementos(int periodo);
        QMap<int, QMap<int, EntidadFederativa*> * > * elementos;
        double nElementosMax;
};


#endif // SERVICIOINFORMACIONESTADISTICA_H
