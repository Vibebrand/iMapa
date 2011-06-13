#ifndef IWIDGETINTERNO_H
#define IWIDGETINTERNO_H
#include <QGraphicsProxyWidget>

class IWidgetInterno
{
public:
    virtual QGraphicsProxyWidget* proxy()=0;
    virtual QWidget* widget()=0;
    virtual void establecerProxy(QGraphicsProxyWidget* proxy);

};

#endif // IWIDGETINTERNO_H
