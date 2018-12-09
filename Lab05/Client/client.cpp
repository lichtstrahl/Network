#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QByteArray>
#include <QProcess>
#include "client.h"

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket())
{
    connect(socket, SIGNAL(connected()), SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), SLOT(sendData()));
    socket->connectToHost(QHostAddress::LocalHost, port);
}

void Client::sendData()
{
    static const quint8 interfaces = 0;
    QDataStream stream(socket);
    quint8 cmd;

    stream >> cmd;

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    for (int i = 0; i < 2; i++)
    {
        QProcess p;
        p.start(interfaces ? "ipconfig" : "route print");
        p.waitForFinished(5000);
        QString str = QString(p.readAllStandardOutput().toStdString().data());
        out << str;

        qDebug() << "Bytes sent" << socket->write(data);
    }
}

void Client::connected()
{
    qDebug() << "Connected to server";
}
