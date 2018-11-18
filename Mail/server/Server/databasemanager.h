#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = nullptr);
    ~DataBaseManager();

    bool launch();
    bool isOpen();

    void close();

signals:
    void sendsMessage(const QString &msg, const QColor &color);

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
