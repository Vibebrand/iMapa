#ifndef ICONTENEDORWIDGETS_H
#define ICONTENEDORWIDGETS_H
#include <QWidget>
#include <QMap>

struct WidgetInterno{
    QWidget *widget;
    QGraphicsProxyWidget *proxy;

    WidgetInterno(QWidget *widget, QGraphicsProxyWidget *proxy)
        : widget(widget), proxy(proxy) {}
};

class IContenedorWidgets
{
public:
    virtual QMap<QString, WidgetInterno>   obtenerWidgetsInternos();
};

#endif // ICONTENEDORWIDGETS_H
