#ifndef IDELEGADOOBJETOBURBUJA_H
#define IDELEGADOOBJETOBURBUJA_H

#include <QColor>

class IDelegadoObjetoBurbuja
{
public:

    virtual void asignarColorAElemento(QColor color) = 0;

    virtual void asignarRadioAElemento(int radio) = 0;

    virtual void establecerVisible(bool visible) = 0;

};


#endif // IDELEGADOOBJETOBURBUJA_H
