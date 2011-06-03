#ifndef CONTROLADORDEBURBUJAS_H
#define CONTROLADORDEBURBUJAS_H

#include <QMap>
#include <QString>
#include <QTimer>

#include "IDelegadoControladorPluginBurbujas.h"
#include "IDelegadoGestorSeleccion.h"
#include "IDelegadoObjetoBurbuja.h"

#include "servicio/ServicioInformacionEstadistica.h"

class ControladorDeBurbujasPrivate;

/*!
Controlador responsable de mostar la informacion estadistcia de acuerdo
a una linea de tiempo impuesta por un periodo de informacion determinado
por el ServicioInformacionEstadistica
*/

class ControladorDeBurbujas:public QObject, public IDelegeadoGestorSeleccion
{
    Q_OBJECT

public:
    ControladorDeBurbujas(IServicioInformacionEstadistica *, QObject *parent = 0);
    ~ControladorDeBurbujas();
    void elementoSeleccionado(QString nombre);
    void asignarDelegadoControladorPluginBurbujas(IDelegadoControladorPluginBurbujas* controladorPluginBurbujas);

public slots:
    void cmdIniciarSecuenciaDePeriodos();
    void cmdAdelantarPeriodo();
    void cmdAtrasarPerioro();
    void agregarBurbujasAlMapa();


signals:
    void cambioDePeriodo();

private:
    IServicioInformacionEstadistica* _servicioInformacionEstadistica;
    IDelegadoControladorPluginBurbujas* _controladorPluginBurbujas;
    QMap<QString, IDelegadoObjetoBurbuja* > _delegadosObjetoBurbuja;
    const QList<EntidadFederativa *>* _entidadesFederativasActivaas;
    int periodoEstadisticoActivo;
    int numeroPeriodos;
    bool animacion;
    QTimer seconds;
    ControladorDeBurbujasPrivate* clasePrivada;
};


#endif // CONTROLADORDEBURBUJAS_H
