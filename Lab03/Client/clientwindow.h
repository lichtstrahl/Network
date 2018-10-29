#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ClientWindow;
}

class QTcpSocket;

enum TextType
{
    TT_Info,
    TT_Warning,
    TT_Error,
    TT_Success
};

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

public slots:
    void print(const QString &text, TextType type = TT_Info);

private:
    Ui::ClientWindow *ui;
    QTcpSocket *socket;

    const quint16 port;

private slots:
    void onSocketConnected();
    void onServerResponse();
    void onSendFile();
};

#endif // CLIENTWINDOW_H
