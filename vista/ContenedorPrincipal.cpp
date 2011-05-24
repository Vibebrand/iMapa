#include "ContenedorPrincipal.h"


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
 private:
    QWidget *widgetFondo;
};

ContenedorPrincipal::ContenedorPrincipal(QObject *parent, QWidget *awidgetDeFondo):
    QObject(parent),
    widgetDeFondo(awidgetDeFondo)
{
    representacionVista = new GraphicsView(0, awidgetDeFondo);

    representacionVista->setScene(&escena);
    representacionVista->setRenderHint(QPainter::Antialiasing);
    representacionVista->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    escena.addWidget(awidgetDeFondo);
}

void ContenedorPrincipal::agregarWidget(QString nombre, QWidget *widget)
{
    widgetsInternos.insert(nombre, WidgetInterno(widget,
                                                  escena.addWidget(widget)));
}

ContenedorPrincipal::~ContenedorPrincipal()
{
    delete representacionVista;
}

QWidget* ContenedorPrincipal::obtenerRepresentacionVista() const
{
    return representacionVista;
}
