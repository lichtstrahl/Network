#include <QTcpSocket>

#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow), socket(nullptr), port(7007)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    socket->connectToHost("localhost", port);
    connect(socket, &QTcpSocket::connected, this, &ClientWindow::onSocketConnected);
}

ClientWindow::~ClientWindow()
{
    delete ui;
    if(socket->isOpen())
        socket->disconnectFromHost();
    delete socket;
}

void ClientWindow::print(const QString &text, TextType type)
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

void ClientWindow::onSocketConnected()
{
    print("Socket has connected to host", TT_Success);
}
