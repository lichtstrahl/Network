#ifndef SERVERSCREEN_H
#define SERVERSCREEN_H

#include <QMainWindow>

namespace Ui {
    class ServerScreen;
}

enum MessageType
{
    MT_INFO,
    MT_WARNING,
    MT_ERROR
};

class ServerScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerScreen(QWidget *parent = 0);
    ~ServerScreen();

    void print(const QString &message, MessageType type = MT_INFO);

private:
    Ui::ServerScreen *ui;
};

#endif // SERVERSCREEN_H
