#ifndef REPRESENTACIONDEVISTA_H
#define REPRESENTACIONDEVISTA_H

#include <QDeclarativeView>
#include "IGestionaEvento.h"
#include "IWidgetInterno.h"
class RepresentacionDeVista : public QDeclarativeView, public IGestionaEvento, public IWidgetInterno
{
public:
    explicit RepresentacionDeVista();
    virtual ~RepresentacionDeVista();
    bool gestionaEvento(QEvent * event);
    void establecerProxy(QGraphicsProxyWidget *proxy);
    QGraphicsProxyWidget* proxy();
    QWidget* widget();
private:
    qreal totalScaleFactor;
    QGraphicsProxyWidget *_proxy;
    QPointF *posicionTouch;
};

#endif // REPRESENTACIONDEVISTA_H
