#ifndef MAPA_H
#define MAPA_H

#include <QWidget>
#include <QMap>
#include <MarbleWidget.h>

#include "IGestionaEvento.h"
#include "servicio/comunicacionRed/IDelegadoComando.h"

class ControladorMapa : public Marble::MarbleWidget, public IGestionaEvento, public IDelegadoComando
{
    Q_OBJECT
public:
    explicit ControladorMapa();
    bool gestionaEvento(QEvent * event);

    QString obtenIdentificador();
    QMap<int, QString> obtenComandos();
    bool comandoSeleccionado(QString);

public slots:
    void gestionaAccionPluginItems(int x, int y);

private:
    QMap<int, QString> comandos;
};

#endif // MAPA_H
