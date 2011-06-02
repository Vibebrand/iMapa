#include "servicio/ServicioInformacionEstadistica.h"

#include <QDebug>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "modelo/EntidadFederativa.h"
#include "modelo/PoblacionPorRangoDeEdad.h"

ServicioInformacionEstadistica::ServicioInformacionEstadistica()
{
    elementos = new QMap<int, QMap<int, EntidadFederativa *> *>;
}

ServicioInformacionEstadistica::~ServicioInformacionEstadistica()
{
    for(QMap<int, QMap<int, EntidadFederativa *> *>::iterator it = elementos->begin(); it != elementos->end(); ++it)
        if(QMap<int, EntidadFederativa *> * elementoInterno = it.value())
        {
            for(QMap<int, EntidadFederativa *>::iterator it2 = elementoInterno->begin(); it2 != elementoInterno->end(); ++it2)
            {
                if(EntidadFederativa * entidadFed = it2.value())
                {
                    delete entidadFed;
                    it2.value() = 0;
                }
            }

            delete elementoInterno;
            it.value() = 0;
        }

    delete elementos;
}

int ServicioInformacionEstadistica::obtenerPeriodos()
{
    return 1;
}

const QList<EntidadFederativa *> * ServicioInformacionEstadistica::obtenerPeriodo(int periodo)
{
    if (!elementos->contains(periodo))
        elementos->insert(periodo, obtenerElementos(periodo));

    return new QList<EntidadFederativa *>( elementos->value(periodo)->values() ) ;
}

double ServicioInformacionEstadistica::obtenerTotalDePoblacionPorPeriodo()
{
    return nElementosMax;
}

QMap<int, EntidadFederativa *> * ServicioInformacionEstadistica::obtenerElementos(int periodo)
{
    QMap<int, EntidadFederativa*> * salida = new QMap<int, EntidadFederativa*>;

    nElementosMax = 0.0;

    QSqlDatabase baseDatos = QSqlDatabase::addDatabase("QSQLITE");
    baseDatos.setDatabaseName("info.sqlite");
    baseDatos.setHostName("localhost");
    if(baseDatos.open())
    {
        qDebug() << "obtenerElementos::open";

        QSqlQuery query("SELECT * FROM mena;");

        int entidadR = query.record().indexOf("entidad");
        int grupoR = query.record().indexOf("grupo");
        int hombresR = query.record().indexOf("hombres");
        int mujeresR = query.record().indexOf("mujeres");

        query.exec();
        while(query.next())
        {
            int entidad = query.value(entidadR).toInt();

            EntidadFederativa * entidadSalida;
            entidadSalida = salida->contains(entidad) ? salida->value(entidad) : new EntidadFederativa;
            entidadSalida->nombre = QString::number(entidad);

            // TODO lectura de BD
            entidadSalida->longitud = -102.3;
            entidadSalida->latitud = 21.883333;

            // TODO lectura incorrecta
            PoblacionPorRangoDeEdad poblacionPorRangoDeEdad;
            poblacionPorRangoDeEdad.nombre = query.value(grupoR).toString();
            poblacionPorRangoDeEdad.numeroDeHombres = query.value(hombresR).toDouble();
            poblacionPorRangoDeEdad.numeroDeMujeres = query.value(mujeresR).toDouble();

            entidadSalida->nHombresPorEntidad += poblacionPorRangoDeEdad.numeroDeHombres;
            entidadSalida->nMujeresPorEntidad += poblacionPorRangoDeEdad.numeroDeMujeres;

            poblacionPorRangoDeEdad.totalDePoblacion = poblacionPorRangoDeEdad.numeroDeHombres + poblacionPorRangoDeEdad.numeroDeMujeres;
            nElementosMax += poblacionPorRangoDeEdad.totalDePoblacion;

            entidadSalida->totalDePoblacion += poblacionPorRangoDeEdad.totalDePoblacion;
            entidadSalida->ragosDeEdad.append(poblacionPorRangoDeEdad);

            (*salida)[entidad] = entidadSalida;
        }

        baseDatos.close();
    }

    return salida;
}
