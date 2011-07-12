#ifndef MAPA_H
#define MAPA_H

#include <QWidget>
#include <MarbleWidget.h>
#include "IGestionaEvento.h"

class ControladorMapa : public Marble::MarbleWidget, public IGestionaEvento
{
    Q_OBJECT
public:
    explicit ControladorMapa();
    bool gestionaEvento(QEvent * event);

public slots:
    void gestionaAccionPluginItems(int x, int y);
};

#endif // MAPA_H
