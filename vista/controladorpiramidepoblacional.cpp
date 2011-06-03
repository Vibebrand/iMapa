#include "controladorpiramidepoblacional.h"
#include <QDebug>
#include <QGraphicsObject>

// TODO calcular ancho de cada elemento del modelo en el controlador (no en la vista)

ControladorPiramidePoblacional::ControladorPiramidePoblacional(QObject *parent) :
    QObject(parent), offset(0), anchoMaximoDeCadaLadoEnPixeles(0), anchoMax(0)
{
    contexto = view.rootContext();
    contexto->setContextProperty("titulo", "Piramide Poblacional");
    contexto->setContextProperty("delegado", this);
    contexto->setContextProperty("modelo", QVariant::fromValue(listaVacia));

    view.setSource(QUrl("qrc:/qml/PiramidePoblacional.qml"));

    bool existePropiedad;
    int tamagnoLista = view.rootObject()->property("tamagnoLista").toInt(&existePropiedad);
    if(existePropiedad)
        this->anchoMaximoDeCadaLadoEnPixeles = tamagnoLista / 2;

    int offset = view.rootObject()->property("offset").toInt(&existePropiedad);
    if(existePropiedad)
        this->offset = offset;
}

ControladorPiramidePoblacional::~ControladorPiramidePoblacional()
{
}


void ControladorPiramidePoblacional::estableceModelo(EntidadFederativa * entidad)
{
    if(contexto)
    {
        anchoMax = 0;

        contexto->setContextProperty("titulo", entidad->nombre);
        contexto->setContextProperty("izqMax", entidad->nHombresPorEntidad);
        contexto->setContextProperty("derMax", entidad->nMujeresPorEntidad);

        listaVacia.clear();
        QList<PoblacionPorRangoDeEdad *> lista = entidad->ragosDeEdad;
        for(QList<PoblacionPorRangoDeEdad *>::iterator it = lista.begin(); it != lista.end(); ++it)
        {
            PoblacionPorRangoDeEdad * pobRangoEdad = (*it);
            int max = pobRangoEdad->getNumeroDeHombres() > pobRangoEdad->getNumeroDeMujeres() ? pobRangoEdad->getNumeroDeHombres() : pobRangoEdad->getNumeroDeMujeres();
            anchoMax = anchoMax > max ? anchoMax : max;

            listaVacia.append(pobRangoEdad);
        }

        contexto->setContextProperty("modelo", QVariant::fromValue(listaVacia));
    }
}

QWidget * ControladorPiramidePoblacional::widget()
{
    return &view;
}

double ControladorPiramidePoblacional::calculaAncho(double cantidad)
{
    return cantidad * anchoMaximoDeCadaLadoEnPixeles / anchoMax;
}

double ControladorPiramidePoblacional::cantidadDesface(double cantidad)
{
    return anchoMaximoDeCadaLadoEnPixeles + offset - calculaAncho(cantidad);
}

