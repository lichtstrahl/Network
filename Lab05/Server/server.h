#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QVector>

class QTcpServer;
class QTcpSocket;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

public slots:
    void clear();
    void printClients();

private:
    QTcpServer *server;
    QVector<QTcpSocket *> clients;
    const quint16 port = 8008;

private slots:
    void clientConnected();
    void clientDisconnected();
    void printData();
};

#endif // SERVER_H
