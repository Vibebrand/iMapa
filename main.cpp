#include <QtGui/QApplication>
#include "MarbleWidget.h"
#include "vista/mapa.h"
#include "vista/ContenedorPrincipal.h"
#include "vista/controladorcontrollineadetiempo.h"
#include "qtuio.h"
#include <QtGui>
#include <QGraphicsView>
#include <GeoDataCoordinates.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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


    int salida = a.exec();


    delete map;
    delete lineaDeTiempo;

    return salida;
}
