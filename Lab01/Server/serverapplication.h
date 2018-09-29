#ifndef SERVERAPPLICATION_H
#define SERVERAPPLICATION_H

#include "./serverscreen.h"
#include "./databasemanager.h"

class ServerApplication
{
public:
    ServerApplication() = default;
    ~ServerApplication();

    void start();
    void stop();

private:
    ServerScreen window;
    DataBaseManager manager;

};

#endif // SERVERAPPLICATION_H
