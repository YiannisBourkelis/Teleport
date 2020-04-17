#include "client_engine.h"
#include "shared_context.h"
#include "client_session.h"
#include <iostream>
#include <thread>

ClientEngine::ClientEngine()
{

}

void ClientEngine::run()
{
    ClientSession c(teleport::io_context);
    c.ConnectToServer();

    teleport::io_context.run();

    std::cout << "ioservice run done!" << std::endl;
}
