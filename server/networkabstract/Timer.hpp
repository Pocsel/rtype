
#ifndef TIMER_HPP_
# define TIMER_HPP_

#ifdef _WIN32 //windows
#include <windows.h>
#else //unix
#include <sys/time.h>
#endif

#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        struct Timer
        {
        private:
            typedef FUNCTOR2(bool, uint32_t) TimerHandler;

        public:
            Timer(void);
            Timer(uint32_t delay, uint64_t lastOccur, TimerHandler const& handler);
            static uint64_t GetTime(void);

            uint32_t delay;
            uint64_t lastOccur;
            TimerHandler handler;
        };

    }
}

#endif // !TIMER_HPP_
