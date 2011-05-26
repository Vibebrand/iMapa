#include "mapa.h"
#include "MarbleWidgetInputHandler.h"

Mapa::Mapa()
{
}

bool Mapa::gestionaEvento(QEvent * evento)
{
    if(!inputHandler()->eventFilter(this, evento))
        return event(evento);
    return true;
}
