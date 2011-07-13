#ifndef IDELEGADOCOMANDO_H
#define IDELEGADOCOMANDO_H

#include <QString>
#include <QMap>

class IDelegadoComando
{
public:
    virtual QString obtenIdentificador() = 0;
    virtual QMap<int, QString> obtenComandos() = 0;
    virtual bool comandoSeleccionado(QString) = 0;
};

#endif // IDELEGADOCOMANDO_H
