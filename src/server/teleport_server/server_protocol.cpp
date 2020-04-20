#include "server_protocol.h"
#include "../../shared/byte_functions.h"
#include "../../shared/payload_types.h"
#include "../../shared/socket_utils.h"
#include <iostream>
#include "clients.h"

std::vector<char> server_protocol::_send_buffer;
std::vector<char> server_protocol::_rcv_buffer;
tcp::socket *server_protocol::psocket;

server_protocol::server_protocol()
{

}

void server_protocol::AsyncSend()
{
    psocket->async_send(boost::asio::const_buffer(_send_buffer.data(),_send_buffer.size()),
                       [](boost::system::error_code ec, std::size_t)
    {
        if (!ec)
        {
          //do_read_header();
        }
        else
        {
          std::cout << "AsyncSend::error" << std::endl;
          SocketUtils::close_socket(*psocket);
        }
    }
    );
}

void server_protocol::sendWelcomeMessage()
{
    _send_buffer.resize(HEADER_SIZE + MSG_SERVER_W_PAYLOAD_SIZE);
    _send_buffer[HEADER_SIZE - 1] = *payload_types::MSG_SERVER_W;
    addHeader(_send_buffer);

    AsyncSend();
}


void server_protocol::AddNewClient()
{
    Client c = Clients::AddNew();

    _send_buffer.resize(HEADER_SIZE + 3);

    _send_buffer[PAYLOAD_TP_IDX] = *payload_types::CONNECT_REPLY_c;
    _send_buffer[PAYLOAD_START_IDX] = 'A';
    intToBytes(1, _send_buffer[PAYLOAD_START_IDX + 1]);
    _send_buffer[PAYLOAD_START_IDX + 2] = c.id;

    addHeader(_send_buffer);
    AsyncSend();
}

void server_protocol::ProcessHeaderAndPayload(const std::vector<char> &header_buffer, const std::vector<char> &payload_buffer)
{
    if (header_buffer[PAYLOAD_TP_IDX] == *payload_types::CONNECT_C){
          std::cout << "equal CONNECT_C" << std::endl;
          std::cout << "client protocol version: v." << payload_buffer[0] << "." << payload_buffer[1] << std::endl;
          AddNewClient();
    }
    //else if(header_buffer[PAYLOAD_TP_IDX] == *payload_types::msg){
    //    std::cout << "equal CONNECT_C" << std::endl;
    //}
}
