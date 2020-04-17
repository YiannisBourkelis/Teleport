#ifndef SERVER_H
#define SERVER_H

#include "globals.h"

class Server
{
public:
    Server(boost::asio::io_context& io_context, unsigned short port);

    void start();

    void do_accept();
private:
    tcp::acceptor m_acceptor;
};

#endif // SERVER_H
