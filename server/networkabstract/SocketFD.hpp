
#ifndef SOCKETFD_HPP_
# define SOCKETFD_HPP_

# ifdef _WIN32 // windows

#include <windows.h>
//#include <winsock2.h>

namespace Gmgp
{
    namespace Server
    {

        typedef SOCKET SocketFD;

    }
}

# else //unix

namespace Gmgp
{
    namespace Server
    {

        typedef int SocketFD;

    }
}

# endif

#endif // !SOCKETFD_HPP_
