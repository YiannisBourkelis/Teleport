#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include "shared_context.h"
#include "client_state.h"

class ClientSession
{
public:
    ClientSession(boost::asio::io_context &io_context);

    void ConnectToServer();
private:
    ClientState state;
    tcp::resolver::results_type server_endpoints;

    tcp::socket socket_;
    char data_[1024];

    void do_connect();
    void do_read_header();

    void timer_tick(const boost::system::error_code &error);
    boost::asio::deadline_timer t;
    void ConnectionRestrationTimer_tick(const boost::system::error_code& error);
    void StartConnectionRestrationTimer();
    boost::asio::deadline_timer connectionRestrationTimer;
};

#endif // CLIENTSESSION_H
