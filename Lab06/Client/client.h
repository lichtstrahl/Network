#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

namespace Ui {
    class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;
};

#endif // CLIENT_H
