#ifndef IDELEGADOCONTROLADORPLUGIN_H
#define IDELEGADOCONTROLADORPLUGIN_H

#include <QString>
#include <QColor>
#include "IDelegadoGestorSeleccion.h"
#include "IDelegadoObjetoBurbuja.h"
struct Burbuja
{
    QString nombre;
    QColor color;
    int radio;
    qreal longitiud;
    qreal latitud;
};

/*!
Delegado que busca implementarse sobre los plugins encargados
de renderizar las burbujas sobre el mapa para la representacion
de informacion Estadistica
*/
class IDelegadoControladorPluginBurbujas
{
public:
    virtual IDelegadoObjetoBurbuja* agregarElemento(Burbuja burbuja) =0;

    virtual void estableceDelegado(IDelegeadoGestorSeleccion *delegado) = 0;

    //Todo: regresar una lista de Delegados Objeto burbuja
};

#endif // IDELEGADOCONTROLADORPLUGIN_H
