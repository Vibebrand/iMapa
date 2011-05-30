#ifndef CONTROLADORDEBURBUJAS_H
#define CONTROLADORDEBURBUJAS_H

#include "IDelegadoControladorPluginBurbujas.h"
#include "IDelegadoGestorSeleccion.h"
#include "IDelegadoObjetoBurbuja.h"
#include <QMap>
#include <QString>
#include "servicio/ServicioInformacionEstadistica.h"

/*!
Controlador responsable de mostar la informacion estadistcia de acuerdo
a una linea de tiempo impuesta por un periodo de informacion determinado
por el ServicioInformacionEstadistica
*/

class ControladorDeBurbujas:public QObject, public IDelegeadoGestorSeleccion
{
    Q_OBJECT

public:
    ControladorDeBurbujas(QObject *parent);
    ~ControladorDeBurbujas();
    void elementoSeleccionado(QString nombre);
    void asignarDelegadoControladorPluginBurbujas(IDelegadoControladorPluginBurbujas* controladorPluginBurbujas);

public slots:
    void agregarBurbujasAlMapa();
private:
    IServicioInformacionEstadistica* _servicioInformacionEstadistica;
    IDelegadoControladorPluginBurbujas* _controladorPluginBurbujas;
    QMap<QString, IDelegadoObjetoBurbuja* > _delegadosObjetoBurbuja;
    QList<EntidadFederativa>* _entidadesFederativasActivaas;
    int periodoEstadisticoActivo;
};


#endif // CONTROLADORDEBURBUJAS_H
