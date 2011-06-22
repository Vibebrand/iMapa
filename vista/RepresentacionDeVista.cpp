#include "RepresentacionDeVista.h"
#include <QTouchEvent>
#include <QDebug>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
RepresentacionDeVista::RepresentacionDeVista() : posicionTouch(0)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    totalScaleFactor=1;

}

bool RepresentacionDeVista::gestionaEvento(QEvent * event)
{
    if(event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchEnd)
    {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>( event )->touchPoints();

        this->viewportEvent(event);

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
                if(scale>=0.7)
                    _proxy->setScale(scale);
            }

            qreal angle = line2.angleTo(line1);

            _proxy->rotate(angle);
            return true;
        }

        switch (event->type()) {

        case QEvent::TouchBegin:

            if(touchPoints.count()==1)
            {
                if(posicionTouch)
                    delete posicionTouch;
                posicionTouch = new QPointF;

                posicionTouch->setX(touchPoints.first().screenPos().x());
                posicionTouch->setY(touchPoints.first().screenPos().y());
            }
            break;

        case QEvent::TouchUpdate:
            if(posicionTouch)
            {
                QPointF nPos;
                nPos.setX(touchPoints.first().screenPos().x());
                nPos.setY(touchPoints.first().screenPos().y());

                qreal difx = nPos.x() - posicionTouch->x();
                qreal dify = nPos.y() - posicionTouch->y();

                posicionTouch->setX(posicionTouch->x() + difx);
                posicionTouch->setY(posicionTouch->y() + dify);

                _proxy->setX( _proxy->x() + difx );
                _proxy->setY( _proxy->y() + dify );

                return true;
            }
            break;
        case QEvent::TouchEnd:
            if(posicionTouch)
            {
                delete posicionTouch;
                posicionTouch = 0;
            }
            break;
        default:
            eventFilter(this, event);
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

RepresentacionDeVista::~RepresentacionDeVista()
{
    if(posicionTouch)
        delete posicionTouch;
}
