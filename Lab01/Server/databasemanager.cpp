#include <stdexcept>

#include "databasemanager.h"

DataBaseManager::DataBaseManager(QObject *parent) : QObject(parent), db(QSqlDatabase::addDatabase("QPSQL"))
{
}

DataBaseManager::~DataBaseManager()
{
    closeConnection();
}

void DataBaseManager::openConnection()
{
    if (db.isOpen())
        return;

    db.setHostName("127.0.0.1");
    db.setDatabaseName("Network");
    db.setUserName("postgres");
    db.setPassword("123456");

    if (!db.open())
        throw std::runtime_error("Can't connect to db");
}

void DataBaseManager::closeConnection()
{
    if (db.isOpen())
        db.close();
}
