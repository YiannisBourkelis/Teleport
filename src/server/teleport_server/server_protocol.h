#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <vector>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class server_protocol
{
public:
    server_protocol();
    static void ProcessHeader(const std::vector<char> &header_buffer);
    static void sendWelcomeMessage();

    static tcp::socket *psocket;
    static void ProcessHeaderAndPayload(const std::vector<char> &header_buffer, const std::vector<char> &payload_buffer);
private:
    static std::vector<char> _send_buffer;
    static std::vector<char> _rcv_buffer;
    static void AsyncSend();
    static void AddNewClient();
    //static void CheckNewClientConnection();
};

#endif // SERVER_PROTOCOL_H
