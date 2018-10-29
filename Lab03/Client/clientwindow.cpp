#include <QTcpSocket>
#include <QFileDialog>
#include <QHostAddress>
#include <QFile>

#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow), socket(nullptr), port(7007)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &ClientWindow::onSocketConnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientWindow::onServerResponse);
    connect(ui->send_pb, SIGNAL(clicked()), SLOT(onSendFile()));
    socket->connectToHost(QHostAddress::LocalHost, port);
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


void ClientWindow::onServerResponse()
{
    print("---------------------------");
    print("Incoming message from server");

    qint64 message = 0;
    QDataStream stream(socket);

    stream >> message;

    print("Message from server: " + QString::number(message));
}

void ClientWindow::onSendFile()
{
    print("---------------------------");
    QString filename = QFileDialog::getOpenFileName(this, "Select file for transfer");
    QFileInfo info(filename);
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        print("Can't open file!", TT_Error);

        return;
    }

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << info.fileName().toStdString().data();
    stream << quint64(file.size());
    stream << file.readAll();

    print(QString::number(socket->write(data)) + " bytes sent to server");
    socket->flush();
}
