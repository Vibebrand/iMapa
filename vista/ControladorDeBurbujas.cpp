#include "ControladorDeBurbujas.h"
#include <QDebug>
#include <QTimer>


class ControladorDeBurbujasPrivate
{
public:
    double _porcentajeMaximoActivo;
    double radioMaximo;

    EntidadFederativa *entidadConPoblacionMaximaEntrePeriodos;

    ControladorDeBurbujasPrivate();
    void obtenerPorcentajeMaximoActivo(double numeroTotalDePoblacionActiva, const QList<EntidadFederativa *>* entidadesFederativasActivaas );
    double asignarRadioEnFuncionPorcentajeMaximoActivo(EntidadFederativa* entidad);

    void obtenerPoblacionMaximaEntreLosPeriodos(IServicioInformacionEstadistica* servicio);
    double asignarRadioEnFuncionPoblacionMaximaEntrePeriodos(EntidadFederativa* entidad);
};

ControladorDeBurbujasPrivate::ControladorDeBurbujasPrivate()
{
    _porcentajeMaximoActivo=0;
    radioMaximo =50;
    entidadConPoblacionMaximaEntrePeriodos=0;


}

void ControladorDeBurbujasPrivate::obtenerPoblacionMaximaEntreLosPeriodos(IServicioInformacionEstadistica *servicio)
{
    int numueroPeriodos = servicio->obtenerPeriodos();
    const QList<EntidadFederativa *>* entidadesFederativasActivas;
    for(int i=1; i<=numueroPeriodos;i++)
    {
        entidadesFederativasActivas = servicio->obtenerPeriodo(i);
        foreach (EntidadFederativa* entidad, (*entidadesFederativasActivas))
        {
            if(entidadConPoblacionMaximaEntrePeriodos)
            {
                if(entidadConPoblacionMaximaEntrePeriodos->totalDePoblacion < entidad->totalDePoblacion  )
                    entidadConPoblacionMaximaEntrePeriodos = entidad;
            }else
                entidadConPoblacionMaximaEntrePeriodos=entidad;
        }
    }
}

double ControladorDeBurbujasPrivate::asignarRadioEnFuncionPoblacionMaximaEntrePeriodos(EntidadFederativa *entidad)
{
    double radio =  ( entidad->totalDePoblacion * radioMaximo)/ entidadConPoblacionMaximaEntrePeriodos->totalDePoblacion;
    return radio;
}

double ControladorDeBurbujasPrivate::asignarRadioEnFuncionPorcentajeMaximoActivo(EntidadFederativa* entidad)
{
    double _radio = (entidad->porcentajeNacionalDePoblacion * radioMaximo ) / _porcentajeMaximoActivo;
    //qDebug()<< entidad->nombre<<"= "<< entidad->totalDePoblacion<<" " << entidad->porcentajeNacionalDePoblacion<< "*" << radioMaximo << "/" << _porcentajeMaximoActivo << "=" << _radio;
    return _radio;
}

void ControladorDeBurbujasPrivate::obtenerPorcentajeMaximoActivo(double numeroTotalDePoblacionActiva, const QList<EntidadFederativa *>* entidadesFederativasActivaas )
{
    foreach(EntidadFederativa * entidad, (*entidadesFederativasActivaas))
    {
        entidad->porcentajeNacionalDePoblacion = (entidad->totalDePoblacion * 100) / numeroTotalDePoblacionActiva;
        _porcentajeMaximoActivo=(_porcentajeMaximoActivo < entidad->porcentajeNacionalDePoblacion)?entidad->porcentajeNacionalDePoblacion: _porcentajeMaximoActivo;
        //qDebug()<< entidad->nombre << " poblacion=" << entidad->totalDePoblacion << " pocentaje="<< entidad->porcentajeNacionalDePoblacion << "ntpa"<< numeroTotalDePoblacionActiva ;
    }
}


ControladorDeBurbujas::ControladorDeBurbujas(IServicioInformacionEstadistica * servicioInfoEstadistica, QObject *parent):
    QObject(parent), _servicioInformacionEstadistica(servicioInfoEstadistica),
    _controladorPluginBurbujas(0), _entidadesFederativasActivaas(0)
{
    clasePrivada = new ControladorDeBurbujasPrivate;
    periodoEstadisticoActivo = 1;
    numeroPeriodos = _servicioInformacionEstadistica->obtenerPeriodos();
    zoomInicial=0;
    actualizarMapa = new QTimer();
    actualizarMapa->setInterval(10);
    refrecadoDeDatosEnBurbujas.setInterval(4000);
    clasePrivada->obtenerPoblacionMaximaEntreLosPeriodos(_servicioInformacionEstadistica);
    QObject::connect(this, SIGNAL(cambioDePeriodo()), this, SLOT(agregarBurbujasAlMapa()));
    QObject::connect(this, SIGNAL(cambioDePeriodo()), this, SLOT(actualizarEntidadSeleccionada()));
}

void ControladorDeBurbujas::agregarBurbujasAlMapa()
{
    if(_entidadesFederativasActivaas)
        delete _entidadesFederativasActivaas;

    _entidadesFederativasActivaas = _servicioInformacionEstadistica->obtenerPeriodo(periodoEstadisticoActivo);
    //clasePrivada->obtenerPorcentajeMaximoActivo(
      //          _servicioInformacionEstadistica->obtenerTotalDePoblacionPorPeriodo(),
        //        _entidadesFederativasActivaas);

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
                            clasePrivada->asignarRadioEnFuncionPoblacionMaximaEntrePeriodos(entidad));

    }
}

void ControladorDeBurbujas::cmdIniciarSecuenciaDePeriodos()
{

    agregarBurbujasAlMapa();
    QObject::connect(&refrecadoDeDatosEnBurbujas,SIGNAL(timeout()), this, SLOT(cmdAdelantarPeriodo()));

    if(!refrecadoDeDatosEnBurbujas.isActive())
        refrecadoDeDatosEnBurbujas.start();
    if(!actualizarMapa->isActive())
        actualizarMapa->start();
}

void ControladorDeBurbujas::cmdAdelantarPeriodo()
{
    if(periodoEstadisticoActivo < numeroPeriodos)
    {
        periodoEstadisticoActivo++;
        emit cambioDePeriodo();
        qDebug()<< periodoEstadisticoActivo;
    }
    else
    {
        refrecadoDeDatosEnBurbujas.stop();
        actualizarMapa->stop();
    }
}


void ControladorDeBurbujas::cmdAtrasarPerioro()
{
    refrecadoDeDatosEnBurbujas.stop();
    if(!actualizarMapa->isActive())
        actualizarMapa->start();
    if(periodoEstadisticoActivo>1)
    {
        --periodoEstadisticoActivo;
        emit cambioDePeriodo();
        qDebug()<<"atras="<<periodoEstadisticoActivo;
    }else
    {
        periodoEstadisticoActivo=1;
        emit cambioDePeriodo();
        actualizarMapa->stop();
    }

}

void ControladorDeBurbujas::elementoSeleccionado(QString nombre)
{
    if(_entidadesFederativasActivaas)
        foreach(EntidadFederativa * entidad, (*_entidadesFederativasActivaas))
            if(!entidad->nombre.compare(nombre))
            {
                ultimaEntidadSeleccionada = nombre;
                emit entidadSeleccionada(entidad);
                break;
            }
}

void ControladorDeBurbujas::actualizarEntidadSeleccionada()
{
    if(!ultimaEntidadSeleccionada.isNull() &&
            !ultimaEntidadSeleccionada.isEmpty())
        elementoSeleccionado(ultimaEntidadSeleccionada);
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
    if(actualizarMapa)
        delete actualizarMapa;
}

//TODO corregir esto
void ControladorDeBurbujas::actualizarRadio(int zoom)
{
    if(zoomInicial)
        zoomInicial = zoom-1000;
    zoom= zoom-1000;

    double radioResultante  = (zoom * 150 )/1100;
    clasePrivada->radioMaximo =( (radioResultante<= 50) || ( zoom <= zoomInicial)  )?50:radioResultante;
    agregarBurbujasAlMapa();
}

QTimer* ControladorDeBurbujas::periodoDeActualizacionDelMapa()
{
    return actualizarMapa;
}
