#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Protocol
{
public:
    Protocol();
    static void CreateProtocolAndIDRequest(std::vector<char> &send_buffer);
    static void SendConnectionProtocolAndID();
    static tcp::socket *psocket;
    static void ProcessHeaderAndPayload(const std::vector<char> &header_buffer, const std::vector<char> &payload_buffer);
private:
    static std::vector<char> _send_buffer;
    static void AsyncSend();
};

#endif // PROTOCOL_H
