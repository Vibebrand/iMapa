#ifndef CONTROLADORPIRAMIDEPOBLACIONAL_H
#define CONTROLADORPIRAMIDEPOBLACIONAL_H

#include <QObject>
#include <QWidget>
#include <QDeclarativeContext>
#include <QDeclarativeView>

#include "modelo/EntidadFederativa.h"
#include "modelo/PoblacionPorRangoDeEdad.h"

class ControladorPiramidePoblacional : public QObject
{
    Q_OBJECT
public:
    explicit ControladorPiramidePoblacional(QObject *parent = 0);
    virtual ~ControladorPiramidePoblacional();

    QWidget * widget();

signals:

public slots:
    void estableceModelo(EntidadFederativa *);

private:
    QDeclarativeView view;
    QDeclarativeContext * contexto;
    QList<QObject *> listaVacia;
};

#endif // CONTROLADORPIRAMIDEPOBLACIONAL_H
