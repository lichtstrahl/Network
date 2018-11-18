#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>

class QTcpServer;
class QTcpSocket;
class DataBaseManager;

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    ~Communicator();

    QString getServerAddress();
    void sendList(QTcpSocket *receiver);

public slots:
    bool launch();

signals:
    void sendsMessage(const QString &message, const QColor &color);

private:
    const quint16 port = 2525; // Port on which server is listening for incoming commands

    QTcpServer *server;
    DataBaseManager *manager;

private slots:
    void clientConnected();
    void clientData();
    void clientDisconnected();
};

#endif // COMMUNICATOR_H
