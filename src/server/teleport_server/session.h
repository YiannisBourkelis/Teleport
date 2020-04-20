#ifndef SESSION_H
#define SESSION_H

#include "globals.h"
#include <vector>

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
    std::vector<char> header_buffer;
    std::vector<char> _payload_buffer;



    void do_read_header();
    //void do_write(std::size_t length);
    void do_read_payload(size_t payload_length);

};

#endif // SESSION_H
