#include <iostream>
#include "globals.h"
#include "server.h"

using namespace std;

int main()
{
    Server server(globals::io_service, 8087);
    globals::io_service.run();

    return 0;
}
