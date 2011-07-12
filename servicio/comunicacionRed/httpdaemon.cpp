#include "httpdaemon.h"

#include <QTcpSocket>
#include <QStringList>
#include <QDateTime>
#include <QDebug>

HttpDaemon::HttpDaemon(IServicioElementos * servicio, quint16 port, QObject *parent) :
    QTcpServer(parent), servicio(servicio)
{
    listen(QHostAddress::Any, port);
}

void HttpDaemon::incomingConnection(int socket)
{
    if (disabled)
        return;

    QTcpSocket* s = new QTcpSocket(this);
    connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
    s->setSocketDescriptor(socket);
}

void HttpDaemon::pause()
{
    disabled = true;
}

void HttpDaemon::resume()
{
    disabled = false;
}

void HttpDaemon::readClient()
{
    if (disabled)
        return;

    QTcpSocket* socket = (QTcpSocket*)sender();
    if (socket->canReadLine()) {
        QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));

        if (tokens[0] == "GET")
        {

            QTextStream os(socket);
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/html; charset=\"utf-8\"\r\n"
                  "\r\n";

            if(servicio)
            {
                if(tokens[1] == "/elementos")
                    os << obtenElementosFormatoNulo(servicio->obtenElementos());
            }

            socket->close();

            if (socket->state() == QTcpSocket::UnconnectedState) {
                delete socket;
            }
        } else if(tokens[0] == "POST")
        {
            QTextStream os(socket);
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/html; charset=\"utf-8\"\r\n"
                  "\r\n";

            if(servicio)
            {
                QStringList elementosPost = tokens[1].split("/");
                if(elementosPost.length() > 2)
                    if(elementosPost[1] == "elemento")
                    {
                        os << obtenElementosFormatoNulo(servicio->indicarElemento(elementosPost[2]));
                    }
            }

            socket->close();

            if (socket->state() == QTcpSocket::UnconnectedState) {
                delete socket;
            }
        }
    }
}


QString HttpDaemon::obtenElementosFormatoNulo(QMap<int, QString> elementos)
{
    QString salida = "";

    for(QMap<int, QString>::iterator it = elementos.begin(); it != elementos.end(); ++it)
    {
        salida += QString::number(it.key()) + "\t";
        salida += it.value() + "\n";
    }

    return salida;
}

void HttpDaemon::discardClient()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();
}
