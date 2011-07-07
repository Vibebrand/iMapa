#include <QDeclarativeView>
#include <QLayout>
#include <QDebug>
#include <QDeclarativeContext>


#include "controladorcontrollineadetiempo.h"

ControladorControlLineaDeTiempo::ControladorControlLineaDeTiempo(QObject *parent) :
    QObject(parent)
{
    anguloDeRotacion=80;
    periodoActivo=1900;
    view.rootContext()->setContextProperty("delegado", this);
    view.rootContext()->setContextProperty("rotacion", anguloDeRotacion);
    view.rootContext()->setContextProperty("_nombreEntidad", "");
    view.rootContext()->setContextProperty("_animacion", "");
    view.rootContext()->setContextProperty("_porcentajeNacional", "");
    view.rootContext()->setContextProperty("_numeroPoblacion", "");
    view.rootContext()->setContextProperty("_periodoActivo", "1900");

    view.setSource(QUrl("qrc:/qml/ControlLineaDeTiempo.qml"));

    view.setAttribute(Qt::WA_TranslucentBackground);
    view.setStyleSheet("background:transparent;");

    comandos.insert(1, "reproducir");
    comandos.insert(2, "anterior");
    comandos.insert(3, "siguiente");
    comandos.insert(-1, "inegi");

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
    periodoActivo =(!indicador)?periodoActivo-=10:periodoActivo+=10;
    view.rootContext()->setContextProperty("rotacion", anguloDeRotacion);
     view.rootContext()->setContextProperty("_periodoActivo",  (periodoActivo==1920)?1921:periodoActivo );
}

void ControladorControlLineaDeTiempo::estableceModelo(EntidadFederativa *entidad)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    QString porcentaje =  QString("%L2").arg( entidad->porcentajeNacionalDePoblacion);
    long n2 = entidad->totalDePoblacion;
    QString numeroPoblacion = QString("%L2").arg( n2);

    view.rootContext()->setContextProperty("_nombreEntidad", entidad->nombre);
    view.rootContext()->setContextProperty("_porcentajeNacional", porcentaje+"%");
    view.rootContext()->setContextProperty("_numeroPoblacion", numeroPoblacion+" hbt");
    view.rootContext()->setContextProperty("_animacion", "animacionBarraCreciendo");
}

void ControladorControlLineaDeTiempo::cambiaEstado()
{
    view.rootContext()->setContextProperty("_animacion", "animacionBarraDecreciendo");
    view.rootContext()->setContextProperty("_nombreEntidad", "");
    view.rootContext()->setContextProperty("_porcentajeNacional", "");
    view.rootContext()->setContextProperty("_numeroPoblacion", "");
}

QString ControladorControlLineaDeTiempo::obtenIdentificador()
{
    return "linea de tiempo";
}

QMap<int, QString> ControladorControlLineaDeTiempo::obtenComandos()
{
    return comandos;
}

bool ControladorControlLineaDeTiempo::comandoSeleccionado(QString idComandoString)
{
    bool ok = false;
    int idComando = idComandoString.toInt(&ok);
    if(ok)
    {
        switch(idComando)
        {
        case 1:
            emit play();
            return true;
        case 2:
            emit atras();
            return true;
        case 3:
            emit adelante();
            return true;
        }
    }
    return false;
}
