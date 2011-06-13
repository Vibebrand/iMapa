#ifndef CONTENEDORPRINCIPAL_H
#define CONTENEDORPRINCIPAL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QWidget>
#include <QMap>
#include "IWidgetInterno.h"

struct WidgetInterno{
    QWidget *widget;
    QGraphicsProxyWidget *proxy;

    WidgetInterno(QWidget *widget, QGraphicsProxyWidget *proxy)
        : widget(widget), proxy(proxy) {}
};


class ContenedorPrincipal : public QObject
{
    Q_OBJECT
public:
    ContenedorPrincipal(QObject* parent, QWidget* awidgetDeFondo);
    virtual ~ContenedorPrincipal();
    void agregarWidget(QString nombre, IWidgetInterno *widget);
    QWidget* obtenerRepresentacionVista() const;
private:
    QWidget* widgetDeFondo;
    QGraphicsScene *escena;
    QGraphicsView * representacionVista;
    QMap<QString, IWidgetInterno*> widgetsInternos;
};


#endif // CONTENEDORPRINCIPAL_H
