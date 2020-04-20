#include "clients.h"
#include "client.h"

std::vector<Client> Clients::list;
int Clients::clientId;

Clients::Clients()
{
    Clients::clientId = 0;
}

Client& Clients::AddNew()
{
    Client c;
    c.id = ++ Clients::clientId;
    list.emplace_back(std::move(c));
    return list.back();
}
