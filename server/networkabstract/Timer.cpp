
#include "Timer.hpp"

namespace Gmgp
{
    namespace Server
    {

        Timer::Timer(void)
        {
        }

        Timer::Timer(uint32_t delay_, uint64_t lastOccur_, TimerHandler const& handler_)
            : delay(delay_), lastOccur(lastOccur_), handler(handler_)
        {
        }

#ifdef _WIN32 //windows

        uint64_t Timer::GetTime(void)
        {
            uint64_t t;
            FILETIME ft;
            GetSystemTimeAsFileTime(&ft);
            t = ft.dwHighDateTime;
            t <<= 32;
            t |= ft.dwLowDateTime;
            t /= 10000;
            return t;
        }

#else //unix

        uint64_t Timer::GetTime(void)
        {
            uint64_t t;
            struct timeval tv;
            gettimeofday(&tv, 0);
            t = tv.tv_sec;
            t *= 1000;
            t += tv.tv_usec / 1000;
            return t;
        }

#endif

    }
}
