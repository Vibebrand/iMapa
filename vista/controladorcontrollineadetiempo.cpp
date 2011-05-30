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
    emit atras();
}

void ControladorControlLineaDeTiempo::playClicked()
{
    emit play();
}

void ControladorControlLineaDeTiempo::adelanteClicked()
{
    emit adelante();
}

QWidget * ControladorControlLineaDeTiempo::widget()
{
    return &view;
}
