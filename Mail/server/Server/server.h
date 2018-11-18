#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

namespace Ui {
    class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

public slots:
    void print(const QString &text, const QColor &color = Qt::black);
    void clear();

private:
    Ui::Server *ui;
};

#endif // SERVER_H
