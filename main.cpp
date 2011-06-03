#include <QtGui/QApplication>
#include <QtGui>
#include <QGraphicsView>
#include <GeoDataCoordinates.h>

#include "MarbleWidget.h"
#include "MarbleMap.h"
#include "RenderPlugin.h"

#include "vista/mapa.h"
#include "vista/ContenedorPrincipal.h"
#include "vista/controladorcontrollineadetiempo.h"
#include "vista/IDelegadoControladorPluginBurbujas.h"
#include "vista/controladorpiramidepoblacional.h"
#include "servicio/IServicioInformacionEstadistica.h"
#include "vista/ControladorDeBurbujas.h"
#include "qtuio.h"

void enlazarPluginAControlador(Mapa * mapWidget, ControladorDeBurbujas * controlador);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mapa* map = new Mapa;
    IServicioInformacionEstadistica * servicioInfoEstadistica = new ServicioInformacionEstadistica;
    ControladorDeBurbujas * controladorBurbujas = new ControladorDeBurbujas(servicioInfoEstadistica);
    ControladorPiramidePoblacional * controladorPiramidePoblacional = new ControladorPiramidePoblacional;
    ControladorControlLineaDeTiempo * lineaDeTiempo = new ControladorControlLineaDeTiempo;
    ContenedorPrincipal * contenedor = new ContenedorPrincipal(0, map);

    map->setObjectName("mapa");
    map->setMapThemeId("earth/srtm/srtm.dgml");
    map->setMapQuality(Marble::LowQuality,Marble::Still);
    map->setMapQuality(Marble::LowQuality, Marble::Animation);

    map->centerOn(-102.71667, 21.85);

    //contenedor->agregarWidget("controladorPiramidePoblacional", controladorPiramidePoblacional->widget());
    contenedor->agregarWidget("lineaDeTiempo", lineaDeTiempo->widget());

    QGraphicsView * view = qobject_cast<QGraphicsView *>(contenedor->obtenerRepresentacionVista());

    QTuio tuio(view);
    contenedor->obtenerRepresentacionVista()->showFullScreen();
    tuio.run();

    enlazarPluginAControlador(map, controladorBurbujas);
    QObject::connect(lineaDeTiempo, SIGNAL(play()), controladorBurbujas, SLOT(cmdIniciarSecuenciaDePeriodos()));

    int salida = a.exec();

    delete contenedor;
    delete lineaDeTiempo;
    delete controladorPiramidePoblacional;
    delete controladorBurbujas;
    delete servicioInfoEstadistica;
    delete map;

    return salida;
}

void enlazarPluginAControlador(Mapa * mapWidget, ControladorDeBurbujas * controlador)
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
