#include "mapa.h"

Mapa::Mapa()
{
}

bool Mapa::gestionaEvento(QEvent * evento)
{
    return event(evento);
}
