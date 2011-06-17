#ifndef CONTROLADORCONTROLLINEADETIEMPO_H
#define CONTROLADORCONTROLLINEADETIEMPO_H

#include <QObject>
#include <QWidget>
#include <QDeclarativeView>
#include "RepresentacionDeVista.h"
#include "IWidgetInterno.h"

class ControladorControlLineaDeTiempo : public QObject
{
    Q_OBJECT
public:
    explicit ControladorControlLineaDeTiempo(QObject *parent = 0);

    Q_INVOKABLE void atrasClicked();
    Q_INVOKABLE void playClicked();
    Q_INVOKABLE void adelanteClicked();

    IWidgetInterno * widget();

signals:
    void atras();
    void play();
    void adelante();

public slots:
    void cambioDePeriodo();

private:
    RepresentacionDeVista view;
    int anguloDeRotacion;

};

#endif // CONTROLADORCONTROLLINEADETIEMPO_H
