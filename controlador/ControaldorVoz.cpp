#include "ControladorVoz.h"
#include <QDebug>

ControladorVoz::ControladorVoz(QObject *parent) : QObject(parent), delegadoComandoActual(0)
{

}

QMap<int, QString> ControladorVoz::obtenElementos()
{
    delegadoComandoActual = 0;
    return listaNombresComando;
}

QMap<int, QString> ControladorVoz::indicarElemento(QString elemento)
{
    if(elemento == "-1")
        return obtenElementos();

    if(!delegadoComandoActual)
    {
        // Buscar comando en lista de comandos
        for(QMap<int, QString>::iterator it = listaNombresComando.begin(); it != listaNombresComando.end(); ++it)
        {
            bool llaveCorrecta = false;
            int indiceComando = elemento.toInt(&llaveCorrecta);
            if(llaveCorrecta && indiceComando >= 0 && indiceComando < delegadoComandos.size())
            {
                delegadoComandoActual = delegadoComandos.at(indiceComando);

                return delegadoComandoActual->obtenComandos();
            }
        }
    } else
    {
        // TODO: Si se quieren comandos anidados, cambiar comportamiento siguiente
        delegadoComandoActual->comandoSeleccionado(elemento);
        return delegadoComandoActual->obtenComandos();
    }

    qDebug() << "Error: ControladorVoz::indicarElemento";
    return obtenElementos();
}

void ControladorVoz::registraDelegadoComando(IDelegadoComando * delegadoComando)
{
    if(delegadoComando && !delegadoComandos.contains(delegadoComando))
    {
        delegadoComandos.append(delegadoComando);
        listaNombresComando.insert(delegadoComandos.size() - 1, delegadoComando->obtenIdentificador());

        delegadoComandoActual = 0;
    }
}
