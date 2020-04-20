#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class SocketUtils
{
    SocketUtils();

public:
    static void close_socket(tcp::socket &socket);
};
#endif // SOCKET_UTILS_H
