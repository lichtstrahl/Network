#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

private:
    QTcpSocket *socket;

    const quint16 port = 8008;

private slots:
    void sendData();
    void connected();
};

#endif // CLIENT_H
