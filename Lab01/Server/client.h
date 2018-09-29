#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

#include "./statuses.h"
#include "./ipaddress.h"

struct client
{
    long id;
    QString name;
    ClientStatus status;
    IPAddress clientAddress;
};

#endif // CLIENT_H
