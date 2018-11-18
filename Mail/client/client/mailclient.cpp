#include "mailclient.h"
#include "ui_mailclient.h"

MailClient::MailClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MailClient)
{
    ui->setupUi(this);
}

MailClient::~MailClient()
{
    delete ui;
}
