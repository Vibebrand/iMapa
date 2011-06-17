#include <QDeclarativeView>
#include <QLayout>
#include <QDebug>
#include <QDeclarativeContext>


#include "controladorcontrollineadetiempo.h"

ControladorControlLineaDeTiempo::ControladorControlLineaDeTiempo(QObject *parent) :
    QObject(parent)
{
    anguloDeRotacion=80;
    view.rootContext()->setContextProperty("delegado", this);
    view.rootContext()->setContextProperty("rotacion", anguloDeRotacion);
    view.rootContext()->setContextProperty("_nombreEntidad", "");
    view.rootContext()->setContextProperty("_porcentajeNacional", "");
    view.rootContext()->setContextProperty("_numeroPoblacion", "");
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
    qDebug() << "Play clicked";
    emit play();
}

void ControladorControlLineaDeTiempo::adelanteClicked()
{
    emit adelante();
}

IWidgetInterno * ControladorControlLineaDeTiempo::widget()
{
    return &view;
}

void ControladorControlLineaDeTiempo::cambioDePeriodo(int indicador)
{
    //TODO: refactoring
    anguloDeRotacion =(indicador)?anguloDeRotacion-=21:anguloDeRotacion+=21;
    view.rootContext()->setContextProperty("rotacion", anguloDeRotacion);
}

void ControladorControlLineaDeTiempo::estableceModelo(EntidadFederativa *entidad)
{
    QString porcentaje =  QString::number( entidad->porcentajeNacionalDePoblacion);
    QString numeroPoblacion = QString::number( entidad->totalDePoblacion);
    view.rootContext()->setContextProperty("_nombreEntidad", entidad->nombre);
    view.rootContext()->setContextProperty("_porcentajeNacional", porcentaje+"%");
    view.rootContext()->setContextProperty("_numeroPoblacion", numeroPoblacion);
}
