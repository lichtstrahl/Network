#include "smtp.h"

SMTP::SMTP( const QString &from, const QString &to, const QString &subject, const QString &body )
{
    socket = new QTcpSocket( this );

    connect( socket, SIGNAL( readyRead() ), this, SLOT( readyRead() ) );
    connect( socket, SIGNAL( connected() ), this, SLOT( connected() ) );
    connect( socket, SIGNAL(error(SocketError)), this,
        SLOT(errorReceived(SocketError)));
    connect( socket, SIGNAL(stateChanged( SocketState)), this,
        SLOT(stateChanged(SocketState)));
    connect(socket, SIGNAL(disconnectedFromHost()), this,
        SLOT(disconnected()));;

    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append(body);
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),
    QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = S_INIT;
    socket->connectToHost( "smtp.yourserver.com", 25);
    if(socket->waitForConnected ( 30000 )) 	{qDebug("connected"); 	}

    t = new QTextStream( socket );
}
SMTP::~SMTP()
{
    delete t;
    delete socket;
}
void SMTP::stateChanged(QTcpSocket::SocketState socketState)
{

    qDebug() <<"stateChanged " << socketState;
}

void SMTP::errorReceived(QTcpSocket::SocketError socketError)
{
    qDebug() << "error " << socketError;
}

void SMTP::disconnected()
{

    qDebug() <<"disconneted";
    qDebug() << "error "  << socket->errorString();
}

void SMTP::connected()
{
    //output->append("connected");
    qDebug() << "Connected ";
}

void SMTP::readyRead()
{

     qDebug() <<"readyRead";
    // SMTP is line-oriented

    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while ( socket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate( 3 );


    if ( state == S_INIT && responseLine[0] == '2' )
    {
        // banner was okay, let's go on

        *t << "HELO there\r\n";
        t->flush();

        state = S_MAIL;
    }
    else if ( state == S_MAIL && responseLine[0] == '2' )
    {
        // HELO response was okay (well, it has to be)

        *t << "MAIL FROM: " << from << "\r\n";
        t->flush();
        state = S_RCPT;
    }
    else if ( state == S_RCPT && responseLine[0] == '2' )
    {

        *t << "RCPT TO: " << rcpt << "\r\n"; //r
        t->flush();
        state = S_DATA;
    }
    else if ( state == S_DATA && responseLine[0] == '2' )
    {

        *t << "DATA\r\n";
        t->flush();
        state = S_BODY;
    }
    else if ( state == S_BODY && responseLine[0] == '3' )
    {

        *t << message << "\r\n.\r\n";
        t->flush();
        state = S_QUIT;
    }
    else if ( state == S_QUIT && responseLine[0] == '2' )
    {

        *t << "QUIT\r\n";
        t->flush();
        // here, we just close.
        state = S_CLOSE;
        emit status( tr( "Message sent" ) );
    }
    else if ( state == S_CLOSE )
    {
        deleteLater();
        return;
    }
    else
    {
        // something broke.
        QMessageBox::warning(nullptr, tr( "Qt Mail Example" ), tr( "Unexpected reply from SMTP server:\n\n" ) + response );
        state = S_CLOSE;
    }
    response = "";
}
