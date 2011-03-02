
#ifndef TCPSOCKET_HPP_
# define TCPSOCKET_HPP_

#ifdef _WIN32 //windows

#include "WindowsTcpSocket.hpp"

namespace Gmgp
{
    namespace Server
    {

        typedef WindowsTcpSocket TcpSocket;

    }
}

#else //unix

#include "UnixTcpSocket.hpp"

namespace Gmgp
{
    namespace Server
    {

        typedef UnixTcpSocket TcpSocket;

    }
}

#endif

#endif // !TCPSOCKET_HPP_
