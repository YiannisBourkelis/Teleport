#include "session.h"
#include <iostream>
#include <thread>

#include "../../shared/payload_types.h"

Session::Session(tcp::socket socket)
    : m_socket(std::move(socket))
{
}

Session::~Session()
{
    std::cout << "session destructor!" << std::endl;
}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket,
                             boost::asio::buffer(data_),
                             boost::asio::transfer_exactly(4),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
              std::cout << "thread id:" << std::this_thread::get_id() << ", data: " << data_ << " size:" << length << std::endl;
              std::string str(data_);
              if (strncmp(&data_[0], payload_types::CONNECT_C ,1) == 0){
                    std::cout << "equal c" << std::endl;
              }
              if (str == "ex\r\n"){
                  std::cout << "will close socket as requested" << std::endl;
                  m_socket.close();
                  return;
              }
              if (str == "te\r\n"){
                  std::cout << "will stop io_service as requested" << std::endl;
                  globals::io_service.stop();
                  return;
              }

              do_write(length);
          }
        });
}

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
