#include "controladorpiramidepoblacional.h"


// TODO calcular ancho de cada elemento del modelo en el controlador (no en la vista)

ControladorPiramidePoblacional::ControladorPiramidePoblacional(QObject *parent) :
    QObject(parent)
{
    contexto = view.rootContext();
    contexto->setContextProperty("titulo", "Piramide Poblacional");
    contexto->setContextProperty("delegado", this);
    contexto->setContextProperty("modelo", QVariant::fromValue(listaVacia));

    view.setSource(QUrl("qrc:/qml/PiramidePoblacional.qml"));
}

ControladorPiramidePoblacional::~ControladorPiramidePoblacional()
{
}


void ControladorPiramidePoblacional::estableceModelo(EntidadFederativa * entidad)
{
    if(contexto)
    {
        contexto->setContextProperty("titulo", entidad->nombre);

        double max = entidad->nHombresPorEntidad > entidad->nMujeresPorEntidad ?
                        entidad->nHombresPorEntidad : entidad->nMujeresPorEntidad;

        contexto->setContextProperty("izqMax", entidad->nHombresPorEntidad);
        contexto->setContextProperty("derMax", entidad->nMujeresPorEntidad);
        contexto->setContextProperty("anchoMax", max);

        listaVacia.clear();
        QList<PoblacionPorRangoDeEdad *> lista = entidad->ragosDeEdad;
        for(QList<PoblacionPorRangoDeEdad *>::iterator it = lista.begin(); it != lista.end(); ++it)
            listaVacia.append((*it));

        contexto->setContextProperty("modelo", QVariant::fromValue(listaVacia));
    }
}

QWidget * ControladorPiramidePoblacional::widget()
{
    return &view;
}
