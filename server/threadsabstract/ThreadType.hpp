#ifndef __THREADTYPE_HPP__
# define __THREADTYPE_HPP__

# ifdef _WIN32 // Windows

#include <Windows.h>

namespace Gmgp
{
    namespace Server
    {

        typedef HANDLE Thread_t;
        typedef HANDLE Mutex_t;

    }
}

# else // Unix

#include <pthread.h>

namespace Gmgp
{
    namespace Server
    {

        typedef pthread_t Thread_t;
        typedef pthread_mutex_t Mutex_t;

    }
}

# endif


#endif /* !__THREADTYPE_HPP__ */

