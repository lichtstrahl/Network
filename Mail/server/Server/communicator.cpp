#include <QTcpServer>
#include <QTcpSocket>
#include <QColor>
#include <QNetworkInterface>
#include <QDataStream>

#include "communicator.h"
#include "databasemanager.h"

Communicator::Communicator(QObject *parent) : QObject(parent), server(new QTcpServer), manager(new DataBaseManager)
{
    connect(manager, SIGNAL(sendsMessage(const QString &, const QColor &)), SIGNAL(sendsMessage(const QString &, const QColor &)));
}

Communicator::~Communicator()
{
    if (server->isListening())
        server->close();

    delete server;

    if (manager->isOpen())
        manager->close();

    delete manager;
}

QString Communicator::getServerAddress()
{
    for (QHostAddress address: QNetworkInterface::allAddresses())
        if (address != QHostAddress::LocalHost && address.toIPv4Address())
            return address.toString();

    return QHostAddress(QHostAddress::LocalHost).toString();
}

void Communicator::sendList(QTcpSocket *receiver)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << QString("Приветственное сообщение");

    receiver->write(data);
    receiver->flush();
}

bool Communicator::launch()
{
    manager->launch();

    if (!server->listen(QHostAddress::Any, port))
    {
        emit sendsMessage(QString("Не удаётся запустить сервер на порту %1").arg(port), Qt::red);
        server->close();

        return false;
    }

    emit sendsMessage(QString("Сервер запущен по адресу  %1:%2").arg(getServerAddress()).arg(port), Qt::green);

    connect(server, SIGNAL(newConnection()), SLOT(clientConnected()));

    return true;
}

void Communicator::clientConnected()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();

    connect(clientSocket, SIGNAL(disconnected()), SLOT(clientDisconnected()));
    connect(clientSocket, SIGNAL(readyRead()), SLOT(clientData()));

    emit sendsMessage(QString("Подключился новый клиент %1").arg(clientSocket->peerAddress().toString()), Qt::gray);
    sendList(clientSocket);
}

void Communicator::clientData()
{
}

void Communicator::clientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    emit sendsMessage(QString("Отключился клиент %1").arg(clientSocket->peerAddress().toString()), Qt::gray);

    clientSocket->deleteLater();
}
