#ifndef CLIENTS_H
#define CLIENTS_H

#include <vector>
#include "client.h"


class Clients
{
public:
    Clients();

    static std::vector<Client> list;

    static Client &AddNew();
private:
    static int clientId;
};

#endif // CLIENTS_H
