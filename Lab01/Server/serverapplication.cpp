#include "serverapplication.h"

ServerApplication::~ServerApplication()
{
    stop();
}

void ServerApplication::start()
{
    window.show();

    try
    {
        manager.openConnection();
        window.print("Connection to database is established!");
    }
    catch(const std::runtime_error &error)
    {
        window.print("Can't establish connection to database!", MT_ERROR);
        window.print("Reason: " + QString(error.what()), MT_INFO);
    }
}

void ServerApplication::stop()
{
    manager.closeConnection();

    window.print("Database connection is closed!");
    window.close();
}
