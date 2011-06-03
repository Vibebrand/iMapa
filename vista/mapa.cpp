#include "mapa.h"
#include "MarbleWidgetInputHandler.h"
#include "IDelegadoObjetoBurbuja.h"

#include <QMouseEvent>
#include <QAction>
#include <QDebug>

#include <MarbleMap.h>
#include <AbstractDataPluginItem.h>

Mapa::Mapa()
{
}

bool Mapa::gestionaEvento(QEvent * evento)
{
    if(!inputHandler()->eventFilter(this, evento))
        return event(evento);
    return true;
}

void Mapa::gestionaAccionPluginItems(int x, int y)
{
    QList<Marble::AbstractDataPluginItem *> items = map()->whichItemAt(QPoint(x, y));
    for(QList<Marble::AbstractDataPluginItem *>::iterator it = items.begin(); it != items.end(); ++it)
        ((Marble::AbstractDataPluginItem *)(*it))->action()->trigger();
}


