#include "RepresentacionDeVista.h"
#include <QTouchEvent>
#include <QDebug>
RepresentacionDeVista::RepresentacionDeVista()
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    totalScaleFactor=1;
}

bool RepresentacionDeVista::gestionaEvento(QEvent * event)
{
    if ( event->type() ==
            QEvent::TouchBegin ||
            event->type() == QEvent::TouchUpdate ||
            event->type() == QEvent::TouchEnd)
    {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>( event )->touchPoints();

        if (touchPoints.count() == 2)
        {
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            QLineF linea1(touchPoint0.startPos(), touchPoint1.startPos());
            QLineF linea2(touchPoint0.pos(), touchPoint1.pos());

            qreal currentScaleFactor = linea2.length()/linea1.length();
            qreal angle = linea2.angleTo(linea1);
            qreal scale = totalScaleFactor * currentScaleFactor;
            qDebug()<<"escala="<<scale;
           _proxy->setScale(scale);
           //_proxy->rotate(angle);

        }
     }
    return eventFilter(this, event);
}

void RepresentacionDeVista::establecerProxy(QGraphicsProxyWidget *proxy)
{
    _proxy = proxy;
}

QGraphicsProxyWidget* RepresentacionDeVista::proxy()
{
    return _proxy;
}

QWidget* RepresentacionDeVista::widget()
{
    return this;
}


