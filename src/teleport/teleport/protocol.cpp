#include "protocol.h"
#include "../../shared/payload_types.h"
#include "../../shared/byte_functions.h"
#include <iostream>

std::vector<char> Protocol::_send_buffer;
tcp::socket *Protocol::psocket;

Protocol::Protocol()
{

}

void Protocol::CreateProtocolAndIDRequest(std::vector<char> &send_buffer)
{
    send_buffer.resize(HEADER_SIZE + PAYLOAD_SIZE_CONNECT_C);

    send_buffer[PAYLOAD_TP_IDX    ] = *payload_types::CONNECT_C;
    send_buffer[PAYLOAD_TP_IDX + 1] = '1';
    send_buffer[PAYLOAD_TP_IDX + 2] = '0';

    addHeader(send_buffer);
}

void Protocol::SendConnectionProtocolAndID()
{
    Protocol::_send_buffer.resize(HEADER_SIZE + PAYLOAD_SIZE_CONNECT_C);

    Protocol::_send_buffer[PAYLOAD_TP_IDX    ] = *payload_types::CONNECT_C;
    Protocol::_send_buffer[PAYLOAD_TP_IDX + 1] = '1';
    Protocol::_send_buffer[PAYLOAD_TP_IDX + 2] = '0';

    addHeader(Protocol::_send_buffer);

    AsyncSend();
}

void Protocol::ProcessHeaderAndPayload(const std::vector<char> &header_buffer, const std::vector<char> &payload_buffer)
{
    if (header_buffer[PAYLOAD_TP_IDX] == *payload_types::MSG_SERVER_W){
          std::cout << "equal MSG_SERVER_W" << std::endl;
          SendConnectionProtocolAndID();
    }
    //else if(header_buffer[PAYLOAD_TP_IDX] == *payload_types::msg){
    //    std::cout << "equal CONNECT_C" << std::endl;
    //}
}

void Protocol::AsyncSend()
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
        }
    }
    );
}
