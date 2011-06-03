#include "ControladorDeBurbujas.h"
#include <QDebug>
#include <QTimer>


class ControladorDeBurbujasPrivate
{
public:
    double _porcentajeMaximoActivo;
    double radioMaximo;
    ControladorDeBurbujasPrivate();
    void obtenerPorcentajeMaximoActivo(double numeroTotalDePoblacionActiva, const QList<EntidadFederativa *>* entidadesFederativasActivaas );
    double asignarRadioEnFuncionPorcentajeMaximoActivo(EntidadFederativa* entidad);
};

ControladorDeBurbujasPrivate::ControladorDeBurbujasPrivate()
{
    _porcentajeMaximoActivo=0;
    radioMaximo =50;
}

double ControladorDeBurbujasPrivate::asignarRadioEnFuncionPorcentajeMaximoActivo(EntidadFederativa* entidad)
{
    double _radio = (entidad->porcentajeNacionalDePoblacion * radioMaximo ) / _porcentajeMaximoActivo;
    //qDebug()<< entidad->nombre<<"  "<< entidad->porcentajeNacionalDePoblacion<< "*" << radioMaximo << "/" << _porcentajeMaximoActivo << "=" << _radio;
    return _radio;
}

void ControladorDeBurbujasPrivate::obtenerPorcentajeMaximoActivo(double numeroTotalDePoblacionActiva, const QList<EntidadFederativa *>* entidadesFederativasActivaas )
{
    foreach(EntidadFederativa * entidad, (*entidadesFederativasActivaas))
    {
        entidad->porcentajeNacionalDePoblacion = (entidad->totalDePoblacion * 100) / numeroTotalDePoblacionActiva;
        _porcentajeMaximoActivo=(_porcentajeMaximoActivo < entidad->porcentajeNacionalDePoblacion)?entidad->porcentajeNacionalDePoblacion: _porcentajeMaximoActivo;
        qDebug()<< entidad->nombre << " poblacion=" << entidad->totalDePoblacion << " pocentaje="<< entidad->porcentajeNacionalDePoblacion  ;
    }
}


ControladorDeBurbujas::ControladorDeBurbujas(IServicioInformacionEstadistica * servicioInfoEstadistica, QObject *parent):
    QObject(parent), _servicioInformacionEstadistica(servicioInfoEstadistica),
    _controladorPluginBurbujas(0), _entidadesFederativasActivaas(0)
{
    clasePrivada = new ControladorDeBurbujasPrivate;
    periodoEstadisticoActivo = 0;
    numeroPeriodos = _servicioInformacionEstadistica->obtenerPeriodos();
    animacion = false;
    zoomInicial=0;
}

void ControladorDeBurbujas::agregarBurbujasAlMapa()
{
    if(_entidadesFederativasActivaas)
        delete _entidadesFederativasActivaas;

    if(animacion)
        cmdAdelantarPeriodo();

    _entidadesFederativasActivaas = _servicioInformacionEstadistica->obtenerPeriodo(periodoEstadisticoActivo);
    clasePrivada->obtenerPorcentajeMaximoActivo(
                _servicioInformacionEstadistica->obtenerTotalDePoblacionPorPeriodo(),
                _entidadesFederativasActivaas);

    foreach(EntidadFederativa * entidad, (*_entidadesFederativasActivaas))
    {
        if(!_delegadosObjetoBurbuja.contains(entidad->nombre))
        {
            Burbuja burbuja;
            burbuja.nombre = entidad->nombre;
            burbuja.latitud = entidad->latitud;
            burbuja.longitud = entidad->longitud;
            burbuja.radio = 0;
            if(_controladorPluginBurbujas)
                _delegadosObjetoBurbuja[burbuja.nombre] = _controladorPluginBurbujas->agregarElemento(burbuja);
        }
        _delegadosObjetoBurbuja[entidad->nombre]->asignarRadioAElemento(
                    clasePrivada->asignarRadioEnFuncionPorcentajeMaximoActivo(
                        entidad));
    }
}

void ControladorDeBurbujas::cmdIniciarSecuenciaDePeriodos()
{
    animacion = true;
    qDebug()<< "iniciada secuencia";
    seconds.setInterval(5000);
    agregarBurbujasAlMapa();
    QObject::connect(&seconds,SIGNAL(timeout()), this, SLOT(agregarBurbujasAlMapa()));
    seconds.start();
}

void ControladorDeBurbujas::cmdAdelantarPeriodo()
{
    if(periodoEstadisticoActivo < numeroPeriodos)
    {
        ++periodoEstadisticoActivo;
        qDebug()<<periodoEstadisticoActivo;
        if(!animacion)
            agregarBurbujasAlMapa();
    }
    else
    {
        animacion = false;
        seconds.stop();
    }
}


void ControladorDeBurbujas::cmdAtrasarPerioro()
{
    animacion = false;
    if(periodoEstadisticoActivo>1)
    {
        --periodoEstadisticoActivo;
        agregarBurbujasAlMapa();
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
    if(clasePrivada)
        delete clasePrivada;
}

void ControladorDeBurbujas::actualizarRadio(int zoom)
{
    if( zoom > zoomInicial)
        clasePrivada->radioMaximo+=10;
    if( zoom < zoomInicial)
        clasePrivada->radioMaximo=(clasePrivada->radioMaximo<0)?0:clasePrivada->radioMaximo-=10;

    zoomInicial =zoom;
    agregarBurbujasAlMapa();
    qDebug()<< "zoom="<< zoom << " radio=" << clasePrivada->radioMaximo;
}
