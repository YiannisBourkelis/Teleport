#include "socket_utils.h"

SocketUtils::SocketUtils()
{

}

void SocketUtils::close_socket(tcp::socket &socket){
    if (socket.is_open()){
        boost::system::error_code e;
        socket.close(e); //close socket and ignore any error
    }
}
