#include "ControladorDeBurbujas.h"
#include <QDebug>

ControladorDeBurbujas::ControladorDeBurbujas(IServicioInformacionEstadistica * servicioInfoEstadistica, QObject *parent):
    QObject(parent), _servicioInformacionEstadistica(servicioInfoEstadistica),
    _controladorPluginBurbujas(0), _entidadesFederativasActivaas(0)
{
}

void ControladorDeBurbujas::agregarBurbujasAlMapa()
{
    if(_entidadesFederativasActivaas)
        delete _entidadesFederativasActivaas;

    _entidadesFederativasActivaas = _servicioInformacionEstadistica->obtenerPeriodo(1);
    periodoEstadisticoActivo = 1;
    double radioMaximo = 100;
    double numeroTotalDePoblacion  = _servicioInformacionEstadistica->obtenerTotalDePoblacionPorPeriodo();
    qDebug() << "numeroTotalDePoblacion: " << numeroTotalDePoblacion;
    foreach(EntidadFederativa * entidad, (*_entidadesFederativasActivaas))
    {
        Burbuja burbuja;
        burbuja.nombre = entidad->nombre;
        burbuja.latitud = entidad->latitud;
        burbuja.longitud = entidad->longitud;
        double porcentajePorEntidad = (entidad->totalDePoblacion * 100) / numeroTotalDePoblacion;
        qDebug() << "(" << entidad->totalDePoblacion  << " * 100) / " << numeroTotalDePoblacion << " = " << porcentajePorEntidad;

        burbuja.radio = (porcentajePorEntidad * radioMaximo ) / 100 ;
        qDebug() <<"-- ent:" << entidad->nombre << " - radio: " << burbuja.radio;

        if(_controladorPluginBurbujas)
            _delegadosObjetoBurbuja[burbuja.nombre] = _controladorPluginBurbujas->agregarElemento(burbuja);

        //break;
    }
}

void ControladorDeBurbujas::elementoSeleccionado(QString nombre)
{
    if(_entidadesFederativasActivaas)
        foreach(EntidadFederativa * entidad, (*_entidadesFederativasActivaas))
            if(entidad->nombre.compare(nombre))
            {
                qDebug()<< entidad->nombre;
                break;
            }
}

void ControladorDeBurbujas::asignarDelegadoControladorPluginBurbujas(IDelegadoControladorPluginBurbujas *controladorPluginBurbujas)
{
    _controladorPluginBurbujas = controladorPluginBurbujas;
}

//TODO verificar que otros objetos se deben de destruir
ControladorDeBurbujas::~ControladorDeBurbujas()
{
    if(_entidadesFederativasActivaas)
        delete _entidadesFederativasActivaas;
}
