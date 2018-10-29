#include <QTcpServer>
#include <QTcpSocket>
#include <QFileDialog>
#include <QFile>

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
    connect(newClient, &QTcpSocket::readyRead, this, &ServerWindow::serveClient);

    print("New client has connected");
}

void ServerWindow::serveClient()
{
    /* Receive */
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    print("---------------------------");
    print("Incoming message from client");

    QDataStream stream(client);
    char *_filename;
    QString filename;
    quint64 size;

    stream >> _filename;
    filename = _filename;
    stream >> size;

    const quint16 maxBlockSize = 32 * 1024;

    print(QString("Filename: ") + filename);
    print("Size: " + QString::number(size));

    /* Save File */
    QString fullFilename = QFileDialog::getExistingDirectory(this, "Save to");
    if (fullFilename.isEmpty())
    {
        print("Save aborted");

        return;
    }

    fullFilename += "/" + filename;
    QFile file(fullFilename);
    if (!file.open(QIODevice::WriteOnly))
    {
        print("Can't open file!", TT_Error);

        return;
    }

    qint64 savedBytes = 0;
    for (quint16 currentBlockSize = size > maxBlockSize ? maxBlockSize : quint16(size);
         size > 0;
         size -= currentBlockSize, currentBlockSize = size > maxBlockSize ? maxBlockSize : quint16(size))
    {
        QByteArray fileData;
        fileData.resize(currentBlockSize);
        stream >> fileData;

        savedBytes += file.write(fileData);
        file.flush();
    }
    file.close();



    /* Reply */
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(savedBytes);
    client->write(data);
    client->flush();

}
