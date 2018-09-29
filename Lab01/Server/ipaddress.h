#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <stdint.h>

struct IPAddress
{
    uint8_t address[4];
    uint16_t port;
};

#endif // IPADDRESS_H
