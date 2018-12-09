#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

class SMTP : public QObject
{
    Q_OBJECT
public:
    SMTP(const QString &from, const QString &to, const QString &subject, const QString &body );
    ~SMTP();

signals:
    void status(const QString &);

private slots:
    void stateChanged(QTcpSocket::SocketState socketState);
    void errorReceived(QTcpSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

private:
    QString message;
    QTextStream *t;
    QTcpSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    int state;

    enum States
    {
        S_RCPT,
        S_MAIL,
        S_DATA,
        S_INIT,
        S_BODY,
        S_QUIT,
        S_CLOSE
    };

};
#endif
