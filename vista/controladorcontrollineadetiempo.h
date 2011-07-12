#ifndef CONTROLADORCONTROLLINEADETIEMPO_H
#define CONTROLADORCONTROLLINEADETIEMPO_H

#include <QObject>
#include <QWidget>
#include <QDeclarativeView>
#include "RepresentacionDeVista.h"
#include "IWidgetInterno.h"
#include "modelo/EntidadFederativa.h"
#include "servicio/comunicacionRed/IDelegadoComando.h"

class ControladorControlLineaDeTiempo : public QObject, public IDelegadoComando
{
    Q_OBJECT
public:
    explicit ControladorControlLineaDeTiempo(QObject *parent = 0);

    Q_INVOKABLE void atrasClicked();
    Q_INVOKABLE void playClicked();
    Q_INVOKABLE void adelanteClicked();
    Q_INVOKABLE void cambiaEstado();

    IWidgetInterno * widget();

    QString obtenIdentificador();
    QMap<int, QString> obtenComandos();
    bool comandoSeleccionado(QString);

signals:
    void atras();
    void play();
    void adelante();

public slots:
    void cambioDePeriodo(int indicador);
    void estableceModelo(EntidadFederativa* entidad);

private:
    QMap<int, QString> comandos;

    RepresentacionDeVista view;
    int anguloDeRotacion;
    int periodoActivo;

};

#endif // CONTROLADORCONTROLLINEADETIEMPO_H
