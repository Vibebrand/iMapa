#ifndef REPRESENTACIONDEVISTA_H
#define REPRESENTACIONDEVISTA_H

#include <QDeclarativeView>
#include "IGestionaEvento.h"
#include "IWidgetInterno.h"
class RepresentacionDeVista : public QDeclarativeView, public IGestionaEvento, public IWidgetInterno
{
public:
    explicit RepresentacionDeVista();
    bool gestionaEvento(QEvent * event);
    void establecerProxy(QGraphicsProxyWidget *proxy);
    QGraphicsProxyWidget* proxy();
    QWidget* widget();
private:
    qreal totalScaleFactor;
    QGraphicsProxyWidget *_proxy;
};

#endif // REPRESENTACIONDEVISTA_H
