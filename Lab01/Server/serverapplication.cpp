#include <QDebug>
#include <QTcpSocket>
#include <QFile>
#include "serverapplication.h"

const int textPort = 6006;
const int filePort = 7007;

const qint8 tcpMessage = 0;
const qint8 tcpFile = 1;

ServerApplication::ServerApplication()
{
    textSocket.bind(QHostAddress::LocalHost, textPort);
    if (!fileServer.listen(QHostAddress::LocalHost, filePort))
    {
        window.print("Can't listen on port " + QString::number(filePort), MT_ERROR);

        fileServer.close();
    }
    else
        window.print("Listening on port " + QString::number(filePort));

    connect(&textSocket, SIGNAL(readyRead()), SLOT(onDataRead()));
    connect(&fileServer, SIGNAL(newConnection()), SLOT(onNewConnection()));
}

ServerApplication::~ServerApplication()
{
    stop();
}

void ServerApplication::start()
{
    window.show();

    try
    {
        manager.openConnection();
        window.print("Connection to database is established!");
    }
    catch(const std::runtime_error &error)
    {
        window.print("Can't establish connection to database!", MT_ERROR);
        window.print("Reason: " + QString(error.what()), MT_INFO);
    }
}

void ServerApplication::stop()
{
    manager.closeConnection();

    window.print("Database connection is closed!");
    window.close();
}

void ServerApplication::onDataRead()
{
    while (textSocket.hasPendingDatagrams())
    {
        window.print("--------------------");
        window.print("Received message on UDP socket");

        QByteArray data;
        data.resize(int(textSocket.pendingDatagramSize()));

        QHostAddress address;
        textSocket.readDatagram(data.data(), data.size(), &address);

        QDataStream stream(data);
        qint16 size;
        stream >> size;
        char *message;
        stream >> message;
        window.print("Incoming message sender address: " + address.toString());
        window.print("Incoming message size: " + QString::number(size));
        window.print("Incoming message: " + QString(message));
        window.print("--------------------");
    }
}

void ServerApplication::onNewConnection()
{
    QTcpSocket *pendingClient = fileServer.nextPendingConnection();
    connect(pendingClient, SIGNAL(disconnected()), pendingClient, SLOT(deleteLater()));
    connect(pendingClient, SIGNAL(readyRead()), SLOT(onFileRead()));
    window.print("New client connected");
}

void ServerApplication::onFileRead()
{
    QTcpSocket *pendingClient = (QTcpSocket *)sender();

    window.print("--------------------");
    window.print("Received message on TCP socket");

    QDataStream stream(pendingClient);
    qint16 size;
    stream >> size;
    qint8 type;
    stream >> type;
    if (type == tcpMessage)
    {
        char *message;
        stream >> message;
        window.print("Incoming message size: " + QString::number(size));
        window.print("Incoming message: " + QString(message));
        window.print("--------------------");
    }
    else
    {
        window.print("Incoming file size: " + QString::number(size));
        QByteArray data;
        stream >> data;

        QFile file("download.bin");
        file.write(data);
        file.close();

        window.print("File saved to download.bin");
        window.print("--------------------");
    }
}
