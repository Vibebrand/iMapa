#ifndef CONTROLMAESTRO_H
#define CONTROLMAESTRO_H

#include <QObject>

#include "MarbleWidget.h"
#include "MarbleMap.h"
#include "RenderPlugin.h"
#include "MarbleWidgetInputHandler.h"

#include "vista/mapa.h"
#include "vista/ContenedorPrincipal.h"
#include "vista/controladorcontrollineadetiempo.h"
#include "vista/IDelegadoControladorPluginBurbujas.h"
#include "vista/controladorpiramidepoblacional.h"
#include "vista/ControladorDeBurbujas.h"
#include "servicio/IServicioInformacionEstadistica.h"
#include "servicio/comunicacionRed/httpdaemon.h"
#include "controlador/ControladorVoz.h"
#include "qtuio.h"

class ControlMaestro : public QObject
{
    Q_OBJECT
public:
    explicit ControlMaestro(QObject *parent = 0);
    virtual ~ControlMaestro();

    void mostrar();
signals:

public slots:

private:
    Mapa * mapa;

    IServicioInformacionEstadistica * servicioInfoEstadistica;
    ControladorDeBurbujas * controladorBurbujas;
    ControladorPiramidePoblacional * controladorPiramidePoblacional;
    ControladorControlLineaDeTiempo * lineaDeTiempo;
    QTuio * tuio;
    ControladorVoz * controladorVoz;
    HttpDaemon * demonio;
    ContenedorPrincipal * contenedor;


    void conectarElementos();
    void configurarMapa();
    void enlazarPluginAControlador(Mapa * mapWidget, ControladorDeBurbujas * controlador);
};

#endif // CONTROLMAESTRO_H
