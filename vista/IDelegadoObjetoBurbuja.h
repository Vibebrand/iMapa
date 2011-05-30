#ifndef IDELEGADOOBJETOBURBUJA_H
#define IDELEGADOOBJETOBURBUJA_H

#include <QColor>

/*!
Delegado implemantado sobre AbsractItems de marble para lamanipulacion
directa del QML en su representacion grafica
*/
class IDelegadoObjetoBurbuja
{
public:

    virtual void asignarColorAElemento(QColor color) = 0;

    virtual void asignarRadioAElemento(int radio) = 0;

    virtual void establecerVisible(bool visible) = 0;

};


#endif // IDELEGADOOBJETOBURBUJA_H
