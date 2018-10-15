#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>

class Client: QObject
{
    Q_OBJECT
public:
    Client();

private:
    QUdpSocket textSocket;

private slots:
    void onDataRead();

public slots:
    void send();
};

#endif // CLIENT_H
