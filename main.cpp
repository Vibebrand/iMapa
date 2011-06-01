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
#include "servicio/IServicioInformacionEstadistica.h"
#include "vista/ControladorDeBurbujas.h"
#include "qtuio.h"

void enlazarPluginAControlador(Mapa * mapWidget, ControladorDeBurbujas * controlador);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IServicioInformacionEstadistica * servicioInfoEstadistica = new ServicioInformacionEstadistica;
    ControladorDeBurbujas * controladorBurbujas = new ControladorDeBurbujas(servicioInfoEstadistica);
    ControladorControlLineaDeTiempo * lineaDeTiempo = new ControladorControlLineaDeTiempo;

    Mapa* map = new Mapa;

    map->setObjectName("mapa");
    map->setMapThemeId("earth/srtm/srtm.dgml");
    map->setMapQuality(Marble::LowQuality,Marble::Still);
    map->setMapQuality(Marble::LowQuality, Marble::Animation);

    ContenedorPrincipal contenedor(0, map);
    contenedor.agregarWidget("lineaDeTiempo", lineaDeTiempo->widget());

    QGraphicsView * view = qobject_cast<QGraphicsView *>(contenedor.obtenerRepresentacionVista());

    QTuio tuio(view);
    contenedor.obtenerRepresentacionVista()->showFullScreen();
    tuio.run();

    enlazarPluginAControlador(map, controladorBurbujas);
    QObject::connect(lineaDeTiempo, SIGNAL(play()), controladorBurbujas, SLOT(agregarBurbujasAlMapa()));

    int salida = a.exec();


    delete map;
    delete lineaDeTiempo;
    delete controladorBurbujas;
    delete servicioInfoEstadistica;

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
