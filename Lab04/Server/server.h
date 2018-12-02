#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QHash>
#include "client.h"

namespace Ui {
    class Server;
}

class QTcpServer;
class QTcpSocket;
class QTimer;

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

    void pushClient(const Client &c);

private:
    Ui::Server *ui;
    QTcpServer *server;
    QHash<QTcpSocket *, Client> clients;
    QTimer *timer;

    static const quint16 port = 7007;
    static const quint16 tokenTime = 500;

private slots:
    void clientConnected();
    void clientDisconnected();
    void moveToken();
    void serveData(Client &client);
};

#endif // SERVER_H
