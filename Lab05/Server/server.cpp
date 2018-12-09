#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include "server.h"

Server::Server(QObject *parent) : QObject(parent), server(new QTcpServer())
{
    connect(server, SIGNAL(newConnection()), SLOT(clientConnected()));

    if (!server->listen(QHostAddress::LocalHost, port))
    {
        qDebug() << "Can't listen on port " + QString::number(port);

        return;
    }

    qDebug() << "Server's been launched on port " + QString::number(port);
    printClients();
}

void Server::clear()
{
    for (int i = 0; i < 50; i++)
        qDebug() << "";
}

void Server::printClients()
{
    if (!clients.count())
        qDebug() << "No clients yet";

    for (int i = 0; i < clients.count(); i++)
        qDebug() << QString("%1   %2:%3").arg(i)
                    .arg(clients[i]->peerAddress().toString())
                    .arg(clients[i]->peerPort());
}

void Server::clientConnected()
{
    QTcpSocket *client = server->nextPendingConnection();
    clients.append(client);
    connect(client, SIGNAL(disconnected()), SLOT(clientDisconnected()));

    clear();
    printClients();

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << quint8(0);
    stream << quint8(1);
    client->write(data);
    client->flush();

    connect(client, SIGNAL(readyRead()), SLOT(printData()));
}

void Server::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    clients.removeOne(client);
    delete client;

    clear();
    printClients();
}

void Server::printData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QDataStream stream(client);
    QString data;
    stream >> data;
    QString line = "";
    for (int i = 0; i < data.count(); i++)
    {
        if (data[i] == '\n' || data[i] == '\r')
        {
            qDebug() << line;
            line = "";
        }
        else
            line += data[i];
    }
    stream >> data;
    line = "";
    for (int i = 0; i < data.count(); i++)
    {
        if (data[i] == '\n' || data[i] == '\r')
        {
            qDebug() << line;
            line = "";
        }
        else
            line += data[i];
    }
}
