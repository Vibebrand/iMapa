#include "controlmaestro.h"

ControlMaestro::ControlMaestro(QObject *parent)
    : QObject(parent),
      mapa(new Mapa),
      servicioInfoEstadistica(new ServicioInformacionEstadistica),
      controladorBurbujas(new ControladorDeBurbujas(servicioInfoEstadistica)),
      controladorPiramidePoblacional(new ControladorPiramidePoblacional),
      lineaDeTiempo(new ControladorControlLineaDeTiempo),
      tuio(new QTuio),
      controladorVoz(new ControladorVoz),
      demonio(new HttpDaemon(controladorVoz, 8080)),
      contenedor(new ContenedorPrincipal(0, mapa))
{
    configurarMapa();
    enlazarPluginAControlador(mapa, controladorBurbujas);
    conectarElementos();
}

ControlMaestro::~ControlMaestro()
{
    delete contenedor;
    delete demonio;
    delete controladorVoz;
    delete tuio;
    delete lineaDeTiempo;
    delete controladorPiramidePoblacional;
    delete controladorBurbujas;
    delete servicioInfoEstadistica;
    delete mapa;
}

void ControlMaestro::conectarElementos()
{
    QObject::connect(mapa->inputHandler(), SIGNAL(mouseClickScreenPosition(int,int)), mapa, SLOT(gestionaAccionPluginItems(int,int)));
    QObject::connect(controladorBurbujas, SIGNAL(entidadSeleccionada(EntidadFederativa*)), controladorPiramidePoblacional, SLOT(estableceModelo(EntidadFederativa*)));
    QObject::connect(controladorBurbujas, SIGNAL(entidadSeleccionada(EntidadFederativa*)), lineaDeTiempo, SLOT(estableceModelo(EntidadFederativa*)));

    QObject::connect(lineaDeTiempo, SIGNAL(play()), controladorBurbujas, SLOT(cmdIniciarSecuenciaDePeriodos()));
    QObject::connect(lineaDeTiempo, SIGNAL(adelante()), controladorBurbujas, SLOT(cmdAdelantarPeriodo()));
    QObject::connect(lineaDeTiempo, SIGNAL(atras()), controladorBurbujas, SLOT(cmdAtrasarPerioro()));
    QObject::connect(controladorBurbujas,SIGNAL(cambioDePeriodo(int)), lineaDeTiempo, SLOT(cambioDePeriodo(int)));

    QObject::connect(controladorBurbujas->periodoDeActualizacionDelMapa(),SIGNAL(timeout()), mapa, SLOT(update()));
    QObject::connect(mapa, SIGNAL(zoomChanged(int)),controladorBurbujas, SLOT(actualizarRadio(int)));
}

void ControlMaestro::configurarMapa()
{
    mapa->setObjectName("mapa");
    mapa->setMapThemeId("earth/srtm/srtm.dgml");
    mapa->setMapQuality(Marble::LowQuality,Marble::Still);
    mapa->setMapQuality(Marble::LowQuality, Marble::Animation);
    mapa->inputHandler()->setMouseButtonPopupEnabled(Qt::LeftButton, false);
    mapa->inputHandler()->setMouseButtonPopupEnabled(Qt::RightButton, false);
    mapa->centerOn(-102.71667, 21.85);
}

void ControlMaestro::mostrar()
{
    contenedor->obtenerRepresentacionVista()->showFullScreen();
    contenedor->agregarWidget("controladorPiramidePoblacional", controladorPiramidePoblacional->widget(), ContenedorPrincipal::DerechaArriba);
    contenedor->agregarWidget("lineaDeTiempo", lineaDeTiempo->widget(), ContenedorPrincipal::IzquierdaAbajo);

    tuio->enlazar(contenedor->obtenerRepresentacionVista());
    tuio->run();
    demonio->resume();
}

void ControlMaestro::enlazarPluginAControlador(Mapa * mapWidget, ControladorDeBurbujas * controlador)
{
    QList<Marble::RenderPlugin *> renderPlugins = mapWidget->map()->renderPlugins();
    for(QList<Marble::RenderPlugin *>::iterator it = renderPlugins.begin(); it != renderPlugins.end(); ++it)
    {
        if (IDelegadoControladorPluginBurbujas * delegado = dynamic_cast<IDelegadoControladorPluginBurbujas *>((*it)))
        {
            controlador->asignarDelegadoControladorPluginBurbujas(delegado);
            delegado->estableceDelegado(controlador);
            break;
        }
    }
}
