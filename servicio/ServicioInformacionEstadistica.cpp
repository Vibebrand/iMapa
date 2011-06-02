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
                if(EntidadFederativa * entidadFed = it2.value())
                {
                    QList<PoblacionPorRangoDeEdad *> rangos = entidadFed->ragosDeEdad;
                    while(rangos.count() > 0)
                        if(PoblacionPorRangoDeEdad * poblacionPorRangoDeEdad = rangos.takeLast())
                        {
                            delete poblacionPorRangoDeEdad;
                            rangos.removeLast();
                        }

                    delete entidadFed;
                    it2.value() = 0;
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
        // TODO: Validar que BD existe...
        QString consulta = QString("SELECT *, g.nombre as grupo, r.nombre as n_entidad FROM mena m LEFT OUTER JOIN grupo_mena g ON m.id_grupo_mena = g.id LEFT OUTER JOIN ref_geo_mena r ON m.entidad = r.id where periodo = ") + QString::number(periodo);
        qDebug() << consulta;
        QSqlQuery query(consulta);

        int entidadR = query.record().indexOf("entidad");
        int grupoR = query.record().indexOf("grupo");
        int hombresR = query.record().indexOf("hombres");
        int mujeresR = query.record().indexOf("mujeres");
        int nEntidadR = query.record().indexOf("n_entidad");
        int longitudR = query.record().indexOf("longitud");
        int latitudR = query.record().indexOf("latitud");

        query.exec();
        while(query.next())
        {
            int entidad = query.value(entidadR).toInt();

            EntidadFederativa * entidadSalida;
            entidadSalida = salida->contains(entidad) ? salida->value(entidad) : new EntidadFederativa;
            entidadSalida->nombre = query.value(nEntidadR).toString();

            entidadSalida->longitud = query.value(longitudR).toDouble();
            entidadSalida->latitud = query.value(latitudR).toDouble();

            PoblacionPorRangoDeEdad * poblacionPorRangoDeEdad = new PoblacionPorRangoDeEdad;
            poblacionPorRangoDeEdad->setNombre(query.value(grupoR).toString());
            poblacionPorRangoDeEdad->setNumeroDeHombres(query.value(hombresR).toDouble());
            poblacionPorRangoDeEdad->setNumeroDeMujeres(query.value(mujeresR).toDouble());

            entidadSalida->nHombresPorEntidad += poblacionPorRangoDeEdad->getNumeroDeHombres();
            entidadSalida->nMujeresPorEntidad += poblacionPorRangoDeEdad->getNumeroDeMujeres();

            poblacionPorRangoDeEdad->setTotalDePoblacion(poblacionPorRangoDeEdad->getNumeroDeHombres() + poblacionPorRangoDeEdad->getNumeroDeMujeres());
            nElementosMax += poblacionPorRangoDeEdad->getTotalDePoblacion();

            entidadSalida->totalDePoblacion += poblacionPorRangoDeEdad->getTotalDePoblacion();
            entidadSalida->ragosDeEdad.append(poblacionPorRangoDeEdad);

            (*salida)[entidad] = entidadSalida;
        }

        baseDatos.close();
    }

    return salida;
}
