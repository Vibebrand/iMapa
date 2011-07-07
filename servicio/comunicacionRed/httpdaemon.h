#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>
#include <QString>
#include <QMap>

#include "iservicioelementos.h"

class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpDaemon(IServicioElementos * servicio, quint16 port, QObject *parent = 0);

    void incomingConnection(int socket);
    void pause();
    void resume();

private slots:
    void readClient();
    void discardClient();

private:
    IServicioElementos * servicio;
    bool disabled;

    QString obtenElementosFormatoNulo(QMap<int, QString> elementos);
};

#endif // HTTPDAEMON_H
