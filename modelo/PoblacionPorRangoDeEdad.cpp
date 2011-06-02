#include "modelo/PoblacionPorRangoDeEdad.h"

void PoblacionPorRangoDeEdad::setNombre(QString nombre){
    _nombre = nombre;
}

QString PoblacionPorRangoDeEdad::getNombre()
{
    return _nombre;
}

void PoblacionPorRangoDeEdad::setNumeroDeHombres(double numeroDeHombres)
{
    if(_numeroDeHombres != numeroDeHombres)
    {
        _numeroDeHombres = numeroDeHombres;
        emit numeroDeHombresChanged();
    }
}

double PoblacionPorRangoDeEdad::getNumeroDeHombres()
{
    return _numeroDeHombres;
}

void PoblacionPorRangoDeEdad::setNumeroDeMujeres(double numeroDeMujeres)
{
    if(_numeroDeMujeres != numeroDeMujeres)
    {
        _numeroDeMujeres = numeroDeMujeres;
        emit numeroDeMujeresChanged();
    }
}

double PoblacionPorRangoDeEdad::getNumeroDeMujeres()
{
    return _numeroDeMujeres;
}

void PoblacionPorRangoDeEdad::setTotalDePoblacion(double totalDePoblacion)
{
    if(_totalDePoblacion != totalDePoblacion)
    {
        _totalDePoblacion = totalDePoblacion;
        emit totalDePoblacionChanged();
    }
}

double PoblacionPorRangoDeEdad::getTotalDePoblacion()
{
    return _totalDePoblacion;
}
