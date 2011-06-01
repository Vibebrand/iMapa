#include "ControladorDeBurbujas.h"
#include <QDebug>

ControladorDeBurbujas::ControladorDeBurbujas(IServicioInformacionEstadistica * servicioInfoEstadistica, QObject *parent):
    QObject(parent), _servicioInformacionEstadistica(servicioInfoEstadistica)
{
}

void ControladorDeBurbujas::agregarBurbujasAlMapa()
{
    /*_entidadesFederativasActivaas = _servicioInformacionEstadistica->obtenerPeriodo(1);
    periodoEstadisticoActivo=1;
    qreal radioMaximo = 100;
    int numeroTotalDePoblacion  = _servicioInformacionEstadistica->obtenerTotalDePoblacionPorPeriodo();
    foreach(EntidadFederativa entidad, (*_entidadesFederativasActivaas))
    {*/
        Burbuja burbuja;
        burbuja.nombre = "burbuja";
        burbuja.color = Qt::red;
        burbuja.longitiud = -102.3;
        burbuja.latitud = 21.883333;
        burbuja.radio = 100;

        /*burbuja.nombre = entidad.nombre;
        burbuja.latitud =entidad.latitud;
        burbuja.longitiud=entidad.longitud;
        qreal porcentajePorEntidad = (entidad.totalDePoblacion * 100)/numeroTotalDePoblacion;
        burbuja.radio = (porcentajePorEntidad * radioMaximo )/ 100 ;*/
        if(_controladorPluginBurbujas)
        {
            qDebug() << "ControladorDeBurbujas::agregarBurbujasAlMapa() .. if(_controladorPluginBurbujas)";
            _delegadosObjetoBurbuja[burbuja.nombre] = _controladorPluginBurbujas->agregarElemento(burbuja);
        }
    //}
}

void ControladorDeBurbujas::elementoSeleccionado(QString nombre)
{
    if(_entidadesFederativasActivaas)
        foreach(EntidadFederativa entidad, (*_entidadesFederativasActivaas))
            if(entidad.nombre.compare(nombre))
            {
                qDebug()<< entidad.nombre.toLatin1();
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
