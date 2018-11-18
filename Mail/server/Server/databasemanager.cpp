#include <QSqlError>
#include <QColor>

#include "databasemanager.h"

DataBaseManager::DataBaseManager(QObject *parent) : QObject(parent)
{
}

DataBaseManager::~DataBaseManager()
{
    if (db.isOpen())
        db.close();
}

bool DataBaseManager::launch()
{
    if (db.isOpen())
        return false;

    db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("123456");

    if (!db.open())
    {
        emit sendsMessage(db.lastError().text(), Qt::red);

        return false;
    }

    emit sendsMessage("Соединение с базой данных установлено", Qt::green);

    return true;
}

bool DataBaseManager::isOpen()
{
    return db.isOpen();
}

void DataBaseManager::close()
{
    db.close();
}
