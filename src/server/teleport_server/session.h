#ifndef SESSION_H
#define SESSION_H

#include "globals.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket);
    ~Session();

    void start();
private:
    tcp::socket m_socket;
    enum { max_length = 1024 };
    char data_[max_length];


    void do_read();
    void do_write(std::size_t length);
};

#endif // SESSION_H
