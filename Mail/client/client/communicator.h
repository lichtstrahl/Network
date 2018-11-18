#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>

class QTcpSocket;

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    ~Communicator();

    void launch();

private:
    QTcpSocket *socket;

    // Mail-box server
    const QString hostname = QString("192.168.1.123");
    const quint16 port = 2525;

private slots:
    void serverResponse();
};

#endif // COMMUNICATOR_H
