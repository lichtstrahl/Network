#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTcpSocket>

namespace Ui {
    class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
    QUdpSocket textSocket;
    QTcpSocket fileSocket;

    void sendUDP();
    void sendTCP();

private slots:
    void onSend();
    void onTCPConnected();
    void onGenerate();

};

#endif // CLIENTWINDOW_H
