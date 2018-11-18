#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    connect(ui->clear_pb, SIGNAL(clicked()), SLOT(clear()));
}

Server::~Server()
{
    delete ui;
}

void Server::print(const QString &text, const QColor &color)
{
    ui->terminal_edit->append("<div style=\"color: " +color.name() +";\">" + text + "</div>");
}

void Server::clear()
{
    ui->terminal_edit->clear();
}
