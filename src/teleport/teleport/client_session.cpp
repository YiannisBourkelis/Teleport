#include "client_session.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

ClientSession::ClientSession(boost::asio::io_context &io_context) :
    socket_(io_context),
    t(io_context),
    connectionRestrationTimer(io_context)
{
    state = ClientState::disconnected;
    boost::system::error_code err;
    //timer_tick(err);
}

void ClientSession::ConnectToServer()
{
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
  boost::asio::async_connect(socket_, server_endpoints,
      [this](boost::system::error_code ec, tcp::endpoint)
      {
        if (!ec)
        {
            std::cout << "connected!!!" << std::endl;
            state = ClientState::connected;
            do_read_header();
        }
        else
        {
            std::cout << "error on connect!!!" << std::endl;
            if (socket_.is_open()){
                socket_.close();
            }
            StartConnectionRestrationTimer();
        }
      });
}

void ClientSession::timer_tick(const boost::system::error_code& error)
{
    t.expires_from_now(boost::posix_time::seconds(1));
    t.async_wait(boost::bind(&ClientSession::timer_tick, this, error));
    std::cout << "timer tick >> thread id:" << std::this_thread::get_id() << std::endl;
}


void ClientSession::do_read_header()
{
  boost::asio::async_read(socket_,
      boost::asio::buffer(data_, 1024),
      boost::asio::transfer_exactly(4),
      [this](boost::system::error_code ec, std::size_t )
      {
        if (!ec)
        {
          std::cout << "will call again do_read_header" << std::endl;
          do_read_header();
        }
        else
        {
          std::cout << "will close socket" << std::endl;
          state = ClientState::disconnected;
          socket_.close();
          StartConnectionRestrationTimer();
        }
      });
}

void ClientSession::StartConnectionRestrationTimer()
{
    if (state == ClientState::connectionRestorationTimerActive)
    {
        return;
    }

    boost::system::error_code err;
    connectionRestrationTimer.expires_from_now(boost::posix_time::seconds(1));
    state = ClientState::connectionRestorationTimerActive;
    connectionRestrationTimer.async_wait(boost::bind(&ClientSession::ConnectionRestrationTimer_tick, this, err));
}
void ClientSession::ConnectionRestrationTimer_tick(const boost::system::error_code& error)
{
    if (state == ClientState::connected) {
        connectionRestrationTimer.cancel();
        return;
    }

    std::cout << "ConnectionRestrationTimer_tick >> thread id:" << std::this_thread::get_id() << std::endl;
    ConnectToServer();
    connectionRestrationTimer.expires_from_now(boost::posix_time::seconds(1));
    boost::system::error_code err;
    connectionRestrationTimer.async_wait(boost::bind(&ClientSession::ConnectionRestrationTimer_tick, this, err));
}





