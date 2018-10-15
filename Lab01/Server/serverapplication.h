#ifndef SERVERAPPLICATION_H
#define SERVERAPPLICATION_H

#include <QTcpServer>
#include <QUdpSocket>
#include "./serverscreen.h"
#include "./databasemanager.h"

class ServerApplication: QObject
{
    Q_OBJECT
public:
    ServerApplication();
    ~ServerApplication();

    void start();
    void stop();

private:
    ServerScreen window;
    DataBaseManager manager;
    QUdpSocket textSocket;
    QTcpServer fileServer;

private slots:
    void onDataRead();
    void onNewConnection();
    void onFileRead();
};

#endif // SERVERAPPLICATION_H
