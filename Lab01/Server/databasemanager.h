#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

#include "client.h"

class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = nullptr);
    ~DataBaseManager();

    void openConnection();
    void closeConnection();

    client getClient(long id);
    client getClient(const QString &name);

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
