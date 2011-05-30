#include <QDeclarativeView>
#include <QLayout>
#include <QDebug>
#include <QDeclarativeContext>

#include "controladorcontrollineadetiempo.h"

ControladorControlLineaDeTiempo::ControladorControlLineaDeTiempo(QObject *parent) :
    QObject(parent)
{
    view.rootContext()->setContextProperty("delegado", this);
    view.setSource(QUrl("qrc:/qml/ControlLineaDeTiempo.qml"));

    view.setAttribute(Qt::WA_TranslucentBackground);
    view.setStyleSheet("background:transparent;");
}

void ControladorControlLineaDeTiempo::atrasClicked()
{
    qDebug() << "Atras";
}

void ControladorControlLineaDeTiempo::playClicked()
{
    qDebug() << "Play";
}

void ControladorControlLineaDeTiempo::adelanteClicked()
{
    qDebug() << "Adelante";
}

QWidget * ControladorControlLineaDeTiempo::widget()
{
    return &view;
}
