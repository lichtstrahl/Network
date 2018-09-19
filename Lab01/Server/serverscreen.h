#ifndef SERVERSCREEN_H
#define SERVERSCREEN_H

#include <QMainWindow>

namespace Ui {
    class ServerScreen;
}

class ServerScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerScreen(QWidget *parent = 0);
    ~ServerScreen();

private:
    Ui::ServerScreen *ui;
};

#endif // SERVERSCREEN_H
