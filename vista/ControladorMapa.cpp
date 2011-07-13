#include "ControladorMapa.h"
#include "MarbleWidgetInputHandler.h"
#include "IDelegadoObjetoBurbuja.h"

#include <QMouseEvent>
#include <QAction>
#include <QDebug>

#include <MarbleMap.h>
#include <AbstractDataPluginItem.h>

ControladorMapa::ControladorMapa()
{
    comandos.insert(101, "acercar");
    comandos.insert(102, "alejar");
    comandos.insert(-1, "inegi");
}

bool ControladorMapa::gestionaEvento(QEvent * evento)
{
    if(!inputHandler()->eventFilter(this, evento))
        return event(evento);
    return true;
}

void ControladorMapa::gestionaAccionPluginItems(int x, int y)
{
    QList<Marble::AbstractDataPluginItem *> items = map()->whichItemAt(QPoint(x, y));
    for(QList<Marble::AbstractDataPluginItem *>::iterator it = items.begin(); it != items.end(); ++it)
        ((Marble::AbstractDataPluginItem *)(*it))->action()->trigger();
}

QString ControladorMapa::obtenIdentificador()
{
    return "mapa";
}

QMap<int, QString> ControladorMapa::obtenComandos()
{
    return comandos;
}

bool ControladorMapa::comandoSeleccionado(QString comando)
{
    bool valido = false;
    int idComando = comando.toInt(&valido);
    switch(idComando)
    {
    case 101:
        zoomIn();
        return true;
    case 102:
        zoomOut();
        return true;
    }

    return false;
}


