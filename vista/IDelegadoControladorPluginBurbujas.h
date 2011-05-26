#ifndef IDELEGADOCONTROLADORPLUGIN_H
#define IDELEGADOCONTROLADORPLUGIN_H

#include <QString>
#include <QColor>


struct Burbuja
{
    QString nombre;
    QColor color;
    int radio;
    qreal longitiud;
    qreal latitud;
};

/*!
Delegado que busca implementarse sobre los plugins encargados
de renderizar las burbujas sobre el mapa para la representacion
de informacion Estadistica
*/
class IDelegadoControladorPluginBurbujas
{
public:
    virtual bool agregarElemento(Burbuja burbuja);

    virtual void asignarColorAElemento(QString nombre, QColor color) = 0;

    virtual void asignarRadioAElemento(QString nombre, int radio) = 0;

    virtual void establecerVisible(QString nombre, bool visible) = 0;

    virtual void estableceDelegado(DelegadoElementoGeoInfo *delegado) = 0;
};

#endif // IDELEGADOCONTROLADORPLUGIN_H
