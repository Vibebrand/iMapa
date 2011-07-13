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

    void asignarDelegadoControladorPluginBurbujas(IDelegadoControladorPluginBurbujas* controladorPluginBurbujas);
    QTimer* periodoDeActualizacionDelMapa();
public slots:
    void elementoSeleccionado(QString nombre);
    void cmdIniciarSecuenciaDePeriodos();
    void cmdAdelantarPeriodo();
    void cmdAtrasarPerioro();
    void agregarBurbujasAlMapa();
    void actualizarRadio(int zoom);
    void actualizarEntidadSeleccionada();

signals:
    void cambioDePeriodo(int indicador);
    void cambioDePeriodo();
    void entidadSeleccionada(EntidadFederativa *entidad);

private:
    IServicioInformacionEstadistica* _servicioInformacionEstadistica;
    IDelegadoControladorPluginBurbujas* _controladorPluginBurbujas;
    QMap<QString, IDelegadoObjetoBurbuja* > _delegadosObjetoBurbuja;
    const QList<EntidadFederativa *>* _entidadesFederativasActivaas;
    int periodoEstadisticoActivo;
    QString ultimaEntidadSeleccionada;
    int numeroPeriodos;
    QTimer refrecadoDeDatosEnBurbujas;
    QTimer *actualizarMapa;
    ControladorDeBurbujasPrivate* clasePrivada;
    int zoomInicial;
};


#endif // CONTROLADORDEBURBUJAS_H
