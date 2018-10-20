#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ServerWindow;
}

enum TextType
{
    TT_Info,
    TT_Warning,
    TT_Error,
    TT_Success
};

class QTcpServer;

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

public slots:
    void print(const QString &text, TextType type=TT_Info);

private:
    Ui::ServerWindow *ui;
    QTcpServer *server;

    const quint16 port;

private slots:
    void newConnection();
    void serverClient();
};

#endif // SERVERWINDOW_H
