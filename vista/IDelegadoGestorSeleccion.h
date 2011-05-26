#ifndef IDELEGADOGESTORSELECCION_H
#define IDELEGADOGESTORSELECCION_H

#include <QString>

class IDelegeadoGestorSeleccion
{

public:
    virtual void ElementoSeleccionado(QString nombre) = 0;

};

#endif // IDELEGADOGESTORSELECCION_H
