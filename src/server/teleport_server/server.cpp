#include "server.h"
#include <iostream>

#include "session.h"

Server::Server(boost::asio::io_context &io_context,unsigned short port)
    : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{

    std::cout << m_acceptor.local_endpoint().address().to_string() << std::endl;

    do_accept();
}

void Server::do_accept()
{
  m_acceptor.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket)
      {
        if (!ec)
        {
          std::cout << socket.remote_endpoint().address().to_string() << std::endl;
          std::make_shared<Session>(std::move(socket))->start();
        }

        do_accept();
      });
}

void Server::start()
{

}
