#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server),
    server(new QTcpServer()),
    timer(new QTimer())
{
    ui->setupUi(this);

    connect(server, SIGNAL(newConnection()), SLOT(clientConnected()));

    if (!server->listen(QHostAddress::LocalHost, port))
    {
        ui->clientsView->hide();
        QLabel *label = new QLabel("<div style=\"color: red\">Can't listen on port " +
                                   QString::number(port) + "</div>", ui->centralWidget);
        label->show();
    };

    ui->clientsView->setRowCount(0);
    ui->clientsView->setColumnCount(4);
    ui->clientsView->setHorizontalHeaderLabels(headers);

    connect(timer, SIGNAL(timeout()), SLOT(moveToken()));
    timer->start(tokenTime);
}

Server::~Server()
{
    delete ui;
}

void Server::pushClient(const Client &c)
{
    clients[c.socket] = c;
    int row = ui->clientsView->rowCount();
    clients[c.socket].name = QString("%1:%2")
            .arg(c.socket->peerAddress().toString())
            .arg(c.socket->peerPort());

    ui->clientsView->insertRow(ui->clientsView->rowCount());
    ui->clientsView->setItem(row, 0, new QTableWidgetItem(clients[c.socket].name));
    ui->clientsView->setItem(row, 1, new QTableWidgetItem("No"));
    ui->clientsView->setItem(row, 2, new QTableWidgetItem("0"));
    ui->clientsView->setItem(row, 3, new QTableWidgetItem("0"));
}

void Server::clientConnected()
{
    QTcpSocket *socket = server->nextPendingConnection();
    pushClient({ .name = "Name", .hasToken = false, .pendingFile = false,
                 .fileProgress = 0, .filesLoaded = 0, .socket = socket });

    connect(socket, SIGNAL(disconnected()), SLOT(clientDisconnected()));
}

void Server::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    Client c = clients[socket];

    if (c.hasToken)
        moveToken();

    ui->clientsView->removeRow(ui->clientsView->findItems(c.name, Qt::MatchFixedString)[0]->row());
    clients.remove(socket);

    delete socket;
}

void Server::moveToken()
{
    static int token = 0;
    QList<Client> c = clients.values();
    if (!c.count())
        return;


    int previousToken = token;
    token = token >= c.count() - 1 ? 0 : token + 1;

    Client &previousClient = clients[c[previousToken].socket];
    previousClient.hasToken = false;
    Client &client = clients[c[token].socket];
    client.hasToken = true;

    int prevRow = ui->clientsView->findItems(previousClient.name, Qt::MatchFixedString)[0]->row();
    ui->clientsView->setItem(prevRow, 1, new QTableWidgetItem("No"));
    ui->clientsView->setItem(prevRow, 2, new QTableWidgetItem(QString::number(previousClient.fileProgress)));
    ui->clientsView->setItem(prevRow, 3, new QTableWidgetItem(QString::number(previousClient.filesLoaded)));
    ui->clientsView->setItem(ui->clientsView->findItems(client.name, Qt::MatchFixedString)[0]->row(),
            1, new QTableWidgetItem("Yes"));

    if (client.socket->bytesAvailable())
        serveData(client);
}

void Server::serveData(Client &client)
{
    QDataStream stream(client.socket);
    qint64 block;
    qint64 blockSize = sizeof(block);
    bool finished = false;

    while(timer->remainingTime())
    {
        qint64 available = client.socket->bytesAvailable();
        if (available)
        {
            client.fileProgress += available < blockSize ? available : blockSize;
            stream >> block;
            finished = false;
        }
        else if(!finished)
        {
            finished = true;
            client.filesLoaded++;
            client.fileProgress = 0;
        }

        QApplication::processEvents();
    }
}
