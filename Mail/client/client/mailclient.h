#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <QMainWindow>

namespace Ui {
    class MailClient;
}

class MailClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit MailClient(QWidget *parent = nullptr);
    ~MailClient();

private:
    Ui::MailClient *ui;
};

#endif // MAILCLIENT_H
