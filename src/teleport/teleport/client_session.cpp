#include "client_session.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "protocol.h"
#include "../../shared/payload_types.h"
#include "../../shared/socket_utils.h"
#include "../../shared/byte_functions.h"

ClientSession::ClientSession(boost::asio::io_context &io_context) :
    socket_(io_context),
    t(io_context),
    connectionRestrationTimer(io_context)
{
    state = ClientState::disconnected;
    _header_buffer.resize(HEADER_SIZE);
    Protocol::psocket = &socket_;
}

void ClientSession::ConnectToServer()
{
    std::cout << "inside ConnectToServer" << std::endl;
    tcp::resolver resolver(teleport::io_context);
    boost::system::error_code e;
    server_endpoints = resolver.resolve("localhost", "8087", e);
    if (e){
        std::cout << "error resolving server endpoints: " << e.message() << std::endl;
    }

    do_connect();
}


//void ClientSession::do_connect(const tcp::resolver::results_type& endpoints)
void ClientSession::do_connect()
{
  std::cout << "inside do_connect" << std::endl;

  boost::asio::async_connect(socket_, server_endpoints,
      [this](boost::system::error_code ec, tcp::endpoint)
      {
        if (!ec)
        {
            std::cout << "async_connect >> connected!" << std::endl;
            state = ClientState::connected;
            do_read_header();
        }
        else
        {
            std::cout << "async_connect >> error on connect!" << std::endl;
            SocketUtils::close_socket(socket_);
            StartConnectionRestorationTimer();
        }
      });
}


void ClientSession::do_read_header()
{
    std::cout << "inside do_read_header" << std::endl;
    boost::asio::async_read(socket_,
                            boost::asio::buffer(_header_buffer, _header_buffer.size()),
                            boost::asio::transfer_exactly(_header_buffer.size()),
      [this](boost::system::error_code ec, std::size_t )
      {
        if (!ec)
        {
          std::cout << "do_read_header ok" << std::endl;
          do_read_payload(getPayloadSize(_header_buffer));
        }
        else
        {
          std::cout << "will close socket" << std::endl;
          state = ClientState::disconnected;
          SocketUtils::close_socket(socket_);
          StartConnectionRestorationTimer();
        }
      });
}

void ClientSession::do_read_payload(size_t payload_length)
{
    _payload_buffer.resize(payload_length);

    boost::asio::async_read(socket_,
                             boost::asio::buffer(_payload_buffer.data(), _payload_buffer.size()),
                             boost::asio::transfer_exactly(_payload_buffer.size()),
        [this](boost::system::error_code ec, std::size_t)
        {
          if (!ec)
          {
              //std::cout << "thread id:" << std::this_thread::get_id() << " do_read_payload, data: " << data_ << " size:" << length << std::endl;
              std::cout << "do_read_payload ok" << std::endl;
              Protocol::ProcessHeaderAndPayload(_header_buffer, _payload_buffer);

              do_read_header();
          } else {
              SocketUtils::close_socket(socket_);
              StartConnectionRestorationTimer();
          }
        });
}


void ClientSession::timer_tick(const boost::system::error_code& error)
{
    //t.expires_from_now(boost::posix_time::seconds(1));
    //t.async_wait(boost::bind(&ClientSession::timer_tick, this, error));
    //std::cout << "timer tick >> thread id:" << std::this_thread::get_id() << std::endl;
}

void ClientSession::StartConnectionRestorationTimer()
{
    std::cout << "inside StartConnectionRestrationTimer" << std::endl;
    std::cout << "StartConnectionRestrationTimer >> thread id:" << std::this_thread::get_id() << std::endl;

    boost::system::error_code err;
    connectionRestrationTimer.cancel(); //?????
    connectionRestrationTimer.expires_from_now(boost::posix_time::seconds(3));
    connectionRestrationTimer.async_wait(boost::bind(&ClientSession::ConnectionRestorationTimer_tick, this, err));
}
void ClientSession::ConnectionRestorationTimer_tick(const boost::system::error_code& error)
{
    std::cout << "inside ConnectionRestrationTimer_tick" << std::endl;
    std::cout << "ConnectionRestrationTimer_tick >> thread id:" << std::this_thread::get_id() << std::endl;

    if (error != boost::asio::error::operation_aborted){
        ConnectToServer();
    }
}





