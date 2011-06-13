#ifndef CONTROLADORPIRAMIDEPOBLACIONAL_H
#define CONTROLADORPIRAMIDEPOBLACIONAL_H

#include <QObject>
#include <QWidget>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include "RepresentacionDeVista.h"
#include "modelo/EntidadFederativa.h"
#include "modelo/PoblacionPorRangoDeEdad.h"
#include "IWidgetInterno.h"

class ControladorPiramidePoblacional : public QObject
{
    Q_OBJECT
public:
    explicit ControladorPiramidePoblacional(QObject *parent = 0);
    virtual ~ControladorPiramidePoblacional();

    Q_INVOKABLE double calculaAncho(double cantidad);
    Q_INVOKABLE double cantidadDesface(double cantidad);

    IWidgetInterno * widget();

signals:

public slots:
    void estableceModelo(EntidadFederativa *);

private:
    RepresentacionDeVista view;
    QDeclarativeContext * contexto;
    QList<QObject *> listaVacia;

    int offset;
    double anchoMaximoDeCadaLadoEnPixeles;
    double anchoMax;
};

#endif // CONTROLADORPIRAMIDEPOBLACIONAL_H
