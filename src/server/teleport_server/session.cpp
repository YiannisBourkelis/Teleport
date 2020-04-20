#include "session.h"
#include <iostream>
#include <thread>

#include "../../shared/byte_functions.h"
#include "../../shared/payload_types.h"
#include "../../shared/socket_utils.h"
#include "server_protocol.h"

Session::Session(tcp::socket socket)
    : m_socket(std::move(socket)),
      header_buffer(HEADER_SIZE)
{
    server_protocol::psocket = &m_socket;
}

Session::~Session()
{
    std::cout << "session destructor!" << std::endl;
}

void Session::start()
{
    server_protocol::sendWelcomeMessage();
    do_read_header();
}

void Session::do_read_header()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket,
                             boost::asio::buffer(header_buffer.data(), header_buffer.size()),
                             boost::asio::transfer_exactly(header_buffer.size()),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
              std::cout << "thread id:" << std::this_thread::get_id() << " do_read_header, data: " << data_ << " size:" << length << std::endl;
              do_read_payload(getPayloadSize(header_buffer));
          } else {
              SocketUtils::close_socket(m_socket);
          }
        });
}

void Session::do_read_payload(size_t payload_length)
{
    auto self(shared_from_this());

    _payload_buffer.resize(payload_length);

    boost::asio::async_read(m_socket,
                             boost::asio::buffer(_payload_buffer.data(), _payload_buffer.size()),
                             boost::asio::transfer_exactly(_payload_buffer.size()),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
              std::cout << "thread id:" << std::this_thread::get_id() << " do_read_payload, data: " << data_ << " size:" << length << std::endl;
              server_protocol::ProcessHeaderAndPayload(header_buffer, _payload_buffer);

              do_read_header();
          } else {
              SocketUtils::close_socket(m_socket);
          }
        });
}

/*
void Session::do_write(std::size_t length)
{
  auto self(shared_from_this());
  boost::asio::async_write(m_socket, boost::asio::buffer(data_, length),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          do_read();
        }
      });
}
*/
