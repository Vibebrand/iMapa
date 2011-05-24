#include <QtGui/QApplication>
#include "ventanaprincipal.h"
#include "MarbleWidget.h"
#include "vista/ContenedorPrincipal.h"
#include "qtuio.h"
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton * pushButton = new QPushButton("Hola mundo");
    Marble::MarbleWidget* map = new Marble::MarbleWidget;
   // map->addGeoDataFile("");
    map->setMapThemeId("earth/srtm/srtm.dgml");
    map->setMapQuality(Marble::NormalQuality,Marble::Still);
    map->setMapQuality(Marble::LowQuality, Marble::Animation);

    ContenedorPrincipal contenedor(0, map);

    QTuio tuio(contenedor.obtenerRepresentacionVista());
    contenedor.obtenerRepresentacionVista()->showFullScreen();

    tuio.run();
    int salida = a.exec();


    delete pushButton;
    delete map;
    return salida;
}
