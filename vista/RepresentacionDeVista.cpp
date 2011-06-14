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
    switch (event->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>( event )->touchPoints();

        if(touchPoints.count()>=1)
        {
            const QTouchEvent::TouchPoint &touchPoint = touchPoints.first();
            _proxy->setX( (touchPoint.pos().x()/2)  );
            _proxy->setY( (touchPoint.pos().y()/2)  );
        }

        if (touchPoints.count() == 2)
        {
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            QLineF linea1(touchPoint0.startPos(), touchPoint1.startPos());
            QLineF linea2(touchPoint0.pos(), touchPoint1.pos());

            QLineF line1(touchPoint0.lastScenePos(), touchPoint1.lastScenePos());
            QLineF line2(touchPoint0.scenePos(), touchPoint1.scenePos());
            if (linea1.length()>0)
            {
                qreal currentScaleFactor = linea2.length()/linea1.length();
                qreal scale = totalScaleFactor * currentScaleFactor;
               _proxy->setScale(scale);
            }

            qreal angle = line2.angleTo(line1);

           _proxy->rotate(angle);
        }
        break;
     }
     case QEvent::MouseMove:
     {
         QMouseEvent *e = static_cast<QMouseEvent*>( event );
        _proxy->setX(e->x()/2);
        _proxy->setY(e->y()/2);
        break;
     }
     default:
        eventFilter(this, event);
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
