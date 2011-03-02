
#ifndef CLOCK_HPP_
# define CLOCK_HPP_

#ifdef _WIN32 //windows
#include <windows.h>
#else //unix
#include <sys/time.h>
#endif

namespace Gmgp
{
    namespace Server
    {

        class Clock
        {
        public:
            Clock(void);
            void Reset(void);
            float GetElapsedTime(void) const;

        private:
#ifdef _WIN32 //windows
            LARGE_INTEGER _baseCounter;
			float _frequence;
#else //unix
            struct timeval _baseTime;
#endif
        };

    }
}

#endif // !CLOCK_HPP_
