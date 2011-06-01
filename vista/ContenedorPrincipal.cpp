#include "ContenedorPrincipal.h"

#include "IGestionaEvento.h"

#include <QGLWidget>
#include <QGLFormat>
#include <QDebug>
#include <QCoreApplication>
#include <QApplication>


class GraphicsView: public QGraphicsView
{
public:
    GraphicsView(QWidget* parent, QWidget * widget):
        QGraphicsView(parent)
    {
        widgetFondo = widget;
        setAttribute(Qt::WA_AcceptTouchEvents);
        viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
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
        if(event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd || event->type() == QEvent::TouchUpdate)
        {
            QTouchEvent * evento = static_cast<QTouchEvent*>(event);

            QList<QTouchEvent::TouchPoint> listaTouch = evento->touchPoints();

            QSet<QGraphicsItem *> setItems;

            for(QList<QTouchEvent::TouchPoint>::iterator it = listaTouch.begin(); it != listaTouch.end(); ++it)
            {
                QGraphicsItem * item = scene()->itemAt((*it).screenPos().toPoint());

                if(!setItems.contains(item))
                {
                    setItems.insert(item);

                    if(QGraphicsProxyWidget * graphicWidget = dynamic_cast<QGraphicsProxyWidget *>(item))
                        if(IGestionaEvento * gestor = dynamic_cast<IGestionaEvento*>(graphicWidget->widget()))
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
    escena = new QGraphicsScene();
    representacionVista = new GraphicsView(0, awidgetDeFondo);
    representacionVista->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    representacionVista->setScene(escena);
    representacionVista->setRenderHint(QPainter::Antialiasing);
    representacionVista->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    escena->addWidget(awidgetDeFondo)->setAcceptTouchEvents(true);
}

void ContenedorPrincipal::agregarWidget(QString nombre, QWidget *widget)
{
    WidgetInterno wi = WidgetInterno(widget, escena->addWidget(widget));
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
