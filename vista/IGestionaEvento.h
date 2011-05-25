#ifndef IGESTIONAEVENTO_H
#define IGESTIONAEVENTO_H

#include <QEvent>

class IGestionaEvento
{
public:
    virtual bool gestionaEvento(QEvent * event) = 0;
};

#endif // IGESTIONAEVENTO_H
