#include "clientwindow.h"
#include "ui_clientwindow.h"

const int textPort = 6006;
const int filePort = 7007;

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    connect(ui->send_pb, SIGNAL(clicked()), SLOT(onSend()));
    connect(&fileSocket, SIGNAL(connected()), SLOT(onTCPConnected()));
    connect(ui->generate_pb, SIGNAL(clicked()), SLOT(onGenerate()));
    fileSocket.connectToHost(QHostAddress::LocalHost, filePort);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::sendUDP()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    const QString &msg = ui->message_edit->toPlainText();

    stream << qint16(msg.size());
    stream << msg.toStdString().data();

    textSocket.writeDatagram(data, QHostAddress::LocalHost, textPort);
    ui->message_edit->setText("");
    ui->chat_edit->append(QString("UDP: ") + msg);
}

void ClientWindow::sendTCP()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    const QString &msg = ui->message_edit->toPlainText();

    stream << qint16(msg.size());
    stream << msg.toStdString().data();

    fileSocket.write(data);
    fileSocket.flush();

    ui->message_edit->setText("");
    ui->chat_edit->append(QString("TCP: " + msg));
}

void ClientWindow::onSend()
{
    switch (ui->sendType_combo->currentIndex())
    {
    case 0:
        sendUDP();
        break;

    case 1:
        sendTCP();
        break;
    }
}

void ClientWindow::onTCPConnected()
{
    ui->chat_edit->append("TCP Socket connected to host");
}

void ClientWindow::onGenerate()
{
    QString message;
    int wordCount = ui->wordCount_spin->value();
    int minWordLen = ui->minWordLength_spin->value();
    int maxWordLen = ui->maxWordLength_spin->value();
    int diff = maxWordLen - minWordLen;
    int symbDiff = 'z' - 'a';

    for(int i = 0; i < wordCount; i++)
    {
        int curWordLen = rand()%diff + minWordLen;
        QString curWord;
        for (int j = 0; j < curWordLen; j++)
            curWord += QString(rand()%symbDiff + 'a');

        message += curWord + QString(" ");
    }

    ui->message_edit->append(message);
}
