#include <QTcpServer>
#include <QTcpSocket>

#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow), server(nullptr), port(7007)
{
    ui->setupUi(this);

    server = new QTcpServer(this);

    if(server->listen(QHostAddress::Any, port))
    {
        print("Server's launched on port " + QString::number(port), TT_Success);
        connect(server, &QTcpServer::newConnection, this, &ServerWindow::newConnection);
    }
    else
    {
        print("Can't launch server on port " + QString::number(port), TT_Error);
        server->close();
    }
}

ServerWindow::~ServerWindow()
{
    delete ui;
    if(server->isListening())
        server->close();
    delete server;
}

void ServerWindow::print(const QString &text, TextType type)
{
    QString style = "style=\"color: ";
    switch(type)
    {
    case TT_Info:
        style += "black;\"";
        break;

    case TT_Error:
        style += "red;\"";
        break;

    case TT_Success:
        style += "green;\"";
        break;

    case TT_Warning:
        style += "yellow;\"";
        break;
    }

    QString formated = "<div " + style + ">" + text +"</div>";
    ui->terminal_edit->append(formated);
}

void ServerWindow::newConnection()
{
    QTcpSocket *newClient = server->nextPendingConnection();

    connect(newClient, &QTcpSocket::disconnected, newClient, &QTcpSocket::deleteLater);
    connect(newClient, &QTcpSocket::readyRead, this, &ServerWindow::serverClient);

    print("New client has connected;");
}

void ServerWindow::serverClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    print("Incoming message from client");
}
