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
