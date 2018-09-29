#include "serverscreen.h"
#include "ui_serverscreen.h"

ServerScreen::ServerScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerScreen)
{
    ui->setupUi(this);
}

ServerScreen::~ServerScreen()
{
    delete ui;
}

void ServerScreen::print(const QString &message, MessageType type)
{
    QString formatedMessage;
    switch(type)
    {
    case MT_ERROR:
        formatedMessage = "<div style='color: #FF0000'>" + message + "</div>";
        break;

    case MT_WARNING:
        formatedMessage = "<div style='color: #FFFF00'>" + message + "</div>";
        break;

    case MT_INFO:
    default:
        formatedMessage = "<div>" + message + "</div>";
        break;
    }

    ui->terminalEditor->append( + '\n' + formatedMessage);
}
