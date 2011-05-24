#include <QtGui/QApplication>
#include "ventanaprincipal.h"
#include "MarbleWidget.h"
#include "vista/ContenedorPrincipal.h"
#include "qtuio.h"
#include <QtGui>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton * pushButton = new QPushButton("Hola mundo");
    Marble::MarbleWidget* map = new Marble::MarbleWidget;

    map->setObjectName("mapa");
   // map->addGeoDataFile("");
    map->setMapThemeId("earth/srtm/srtm.dgml");
    map->setMapQuality(Marble::NormalQuality,Marble::Still);
    map->setMapQuality(Marble::LowQuality, Marble::Animation);

    ContenedorPrincipal contenedor(0, map);

    QGraphicsView * view = qobject_cast<QGraphicsView *>(contenedor.obtenerRepresentacionVista());

    map->setAttribute(Qt::WA_AcceptTouchEvents);
    view->setAttribute(Qt::WA_AcceptTouchEvents);
    view->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    contenedor.obtenerRepresentacionVista()->setAttribute(Qt::WA_AcceptTouchEvents);

    QTuio tuio(view);//view->scene());

    contenedor.obtenerRepresentacionVista()->showFullScreen();

    tuio.run();
    int salida = a.exec();


    delete pushButton;
    delete map;
    return salida;
}
