#ifndef POBLACIONPORRANGODEEDAD_H
#define POBLACIONPORRANGODEEDAD_H

#include <QObject>
#include <QString>

class PoblacionPorRangoDeEdad : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nombre READ getNombre WRITE setNombre NOTIFY nombreChanged)
    Q_PROPERTY(double numeroDeHombres READ getNumeroDeHombres WRITE setNumeroDeHombres NOTIFY numeroDeHombresChanged)
    Q_PROPERTY(double numeroDeMujeres READ getNumeroDeMujeres WRITE setNumeroDeMujeres NOTIFY numeroDeMujeresChanged)
    Q_PROPERTY(double totalDePoblacion READ getTotalDePoblacion WRITE setTotalDePoblacion NOTIFY totalDePoblacionChanged)

public:
    void setNombre(QString);
    QString getNombre();
    void setNumeroDeHombres(double);
    double getNumeroDeHombres();
    void setNumeroDeMujeres(double);
    double getNumeroDeMujeres();
    void setTotalDePoblacion(double);
    double getTotalDePoblacion();


private:
    QString _nombre;
    double _numeroDeHombres;
    double _numeroDeMujeres;
    double _totalDePoblacion;

signals:
    void nombreChanged();
    void numeroDeHombresChanged();
    void numeroDeMujeresChanged();
    void totalDePoblacionChanged();
};

#endif // POBLACIONPORRANGODEEDAD_H
