#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

namespace teleport
{
    static boost::asio::io_context io_context;
}

#endif // SHARED_CONTEXT_H
