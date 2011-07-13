#ifndef ISERVICIOELEMENTOS_H
#define ISERVICIOELEMENTOS_H

#include <QMap>
#include <QString>

class IServicioElementos
{
public:
    virtual QMap<int, QString> obtenElementos() = 0;
    virtual QMap<int, QString> indicarElemento(QString elemento) = 0;
};

#endif // ISERVICIOELEMENTOS_H
