#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include "shared_context.h"
#include "client_state.h"

#include <vector>
#include <mutex>

class ClientSession
{
public:
    ClientSession(boost::asio::io_context &io_context);

    void ConnectToServer();
private:
    ClientState state;
    tcp::resolver::results_type server_endpoints;
    std::vector<char> _sendbuffer;
    std::vector<char> _header_buffer;
    std::vector<char> _payload_buffer;

    tcp::socket socket_;

    void do_connect();
    void do_read_header();

    void timer_tick(const boost::system::error_code &error);
    boost::asio::deadline_timer t;
    void ConnectionRestorationTimer_tick(const boost::system::error_code& error);
    void StartConnectionRestorationTimer();
    boost::asio::deadline_timer connectionRestrationTimer;
    void do_read_payload(size_t payload_length);
};

#endif // CLIENTSESSION_H
