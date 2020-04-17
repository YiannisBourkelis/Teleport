#ifndef GLOBALS_H
#define GLOBALS_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class globals
{
public:
    globals();

    static boost::asio::io_service io_service;
};

#endif // GLOBALS_H
