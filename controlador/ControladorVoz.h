#ifndef CONTROLADOR_VOZ_H
#define CONTROLADOR_VOZ_H

#include <QObject>
#include <QList>
#include <QMap>

#include "servicio/comunicacionRed/iservicioelementos.h"
#include "servicio/comunicacionRed/IDelegadoComando.h"

class ControladorVoz : public QObject, public IServicioElementos
{
public:
    ControladorVoz(QObject * parent = 0);

    QMap<int, QString> obtenElementos();
    QMap<int, QString> indicarElemento(QString elemento);

    void registraDelegadoComando(IDelegadoComando * delegadoComando);

private:
    QList<IDelegadoComando *> delegadoComandos;
    QMap<int, QString> listaNombresComando;
    IDelegadoComando * delegadoComandoActual;
};

#endif
