#ifndef MAPA_H
#define MAPA_H

#include <QWidget>
#include <MarbleWidget.h>
#include "IGestionaEvento.h"

class Mapa : public Marble::MarbleWidget, public IGestionaEvento
{
public:
    explicit Mapa();
    bool gestionaEvento(QEvent * event);
};

#endif // MAPA_H
