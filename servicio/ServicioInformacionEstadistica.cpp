#include "servicio/ServicioInformacionEstadistica.h"

#include <QDebug>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

void obtenerElementos();

ServicioInformacionEstadistica::ServicioInformacionEstadistica()
{
    //obtenerElementos();
}

ServicioInformacionEstadistica::~ServicioInformacionEstadistica()
{
}

int ServicioInformacionEstadistica::obtenerPeriodos()
{
    return 1;
}

QList<EntidadFederativa>* ServicioInformacionEstadistica::obtenerPeriodo(int periodo)
{
    return new QList<EntidadFederativa>();
}

qreal ServicioInformacionEstadistica::obtenerTotalDePoblacionPorPeriodo()
{
    return 0.0;
}

void obtenerElementos()
{
    qDebug() << "obtenerElementos";

    QSqlDatabase baseDatos = QSqlDatabase::addDatabase("QSQLITE");
    baseDatos.setDatabaseName("info.sqlite");
    baseDatos.setHostName("localhost");
    if(baseDatos.open())
    {
        qDebug() << "obtenerElementos::open";

        QSqlQuery query("SELECT * FROM mena;");

        int entidad = query.record().indexOf("entidad");
        int grupo = query.record().indexOf("grupo");

        query.exec();
        while(query.next())
        {
            qDebug() << query.value(entidad).toInt() << query.value(grupo).toString();
        }

        baseDatos.close();
        qDebug() << "obtenerElementos::close";
    }
}
