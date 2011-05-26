#include "ContenedorPrincipal.h"

#include "IGestionaEvento.h"

#include <QGLWidget>
#include <QGLFormat>
#include <QDebug>
#include <QCoreApplication>
#include <QApplication>

#define app (static_cast<QApplication *>(QCoreApplication::instance()))

class GraphicsView: public QGraphicsView
{
public:
    GraphicsView(QWidget* parent, QWidget * widget):
        QGraphicsView(parent)
    {
        widgetFondo = widget;
    }
protected:
    void resizeEvent(QResizeEvent *event)
    {
        if(scene())
            scene()->setSceneRect(QRect(QPoint(0,0), event->size()));

        if(widgetFondo)
            widgetFondo->setFixedSize(event->size());

        QGraphicsView::resizeEvent(event);
    }

    bool viewportEvent(QEvent *event)
    {
        if(event->type() == QEvent::Gesture || event->type() == QEvent::GestureOverride)
        {
            QGestureEvent * gesto = static_cast<QGestureEvent *>(event);
            gesto->setWidget(widgetFondo);
            if(IGestionaEvento * gestor = dynamic_cast<IGestionaEvento*>(widgetFondo))
            {
                qDebug() << "Enviando gesto:" << widgetFondo->objectName() ;
                if(gestor->gestionaEvento(event))
                    return true;
            }
        }

        if(event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd || event->type() == QEvent::TouchUpdate)
        {
            QTouchEvent * evento = static_cast<QTouchEvent*>(event);

            qDebug() << "Posteando evento a escena";

            QGraphicsItem * item = scene()->itemAt( evento->touchPoints().first().screenPos().toPoint());
            if(QGraphicsProxyWidget * graphicWidget = dynamic_cast<QGraphicsProxyWidget *>(item))
            {
                if(IGestionaEvento * gestor = dynamic_cast<IGestionaEvento*>(graphicWidget->widget()))
                {
                    qDebug() << "Posteando evento a widget: " << graphicWidget->widget()->objectName();
                    if(gestor->gestionaEvento(event))
                        return true;
                }
            }
        }

        return QGraphicsView::viewportEvent(event);
    }

 private:
    QWidget *widgetFondo;
};

ContenedorPrincipal::ContenedorPrincipal(QObject *parent, QWidget *awidgetDeFondo):
    QObject(parent),
    widgetDeFondo(awidgetDeFondo)
{
    representacionVista = new GraphicsView(0, awidgetDeFondo);
    representacionVista->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    representacionVista->setObjectName("representacionVista");

    representacionVista->setScene(&escena);
    representacionVista->setRenderHint(QPainter::Antialiasing);
    representacionVista->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    escena.addWidget(awidgetDeFondo)->setAcceptTouchEvents(true);
}

void ContenedorPrincipal::agregarWidget(QString nombre, QWidget *widget)
{
    WidgetInterno wi = WidgetInterno(widget, escena.addWidget(widget));
    wi.proxy->setAcceptTouchEvents(true);
    widgetsInternos.insert(nombre, wi);
}

ContenedorPrincipal::~ContenedorPrincipal()
{
    delete representacionVista;
}

QWidget* ContenedorPrincipal::obtenerRepresentacionVista() const
{
    return representacionVista;
}
