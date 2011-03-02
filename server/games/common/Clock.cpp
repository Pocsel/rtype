#include "Log.hpp"
#include "Clock.hpp"

namespace Gmgp
{
    namespace Server
    {

#ifdef _WIN32 //windows

        Clock::Clock(void)
        {
			this->Reset();
        }

        void Clock::Reset(void)
        {
			LARGE_INTEGER freq;
			::QueryPerformanceFrequency(&freq);
			this->_frequence = 1.0f / freq.QuadPart;
			::QueryPerformanceCounter(&this->_baseCounter);
        }

        float Clock::GetElapsedTime(void) const
        {
			LARGE_INTEGER curCount;
            ::QueryPerformanceCounter(&curCount);
			return (curCount.QuadPart - this->_baseCounter.QuadPart) * this->_frequence;
        }

#else //unix

        Clock::Clock(void)
        {
            gettimeofday(&this->_baseTime, 0);
        }

        void Clock::Reset(void)
        {
            gettimeofday(&this->_baseTime, 0);
        }

        float Clock::GetElapsedTime(void) const
        {
            float t;

            struct timeval tv;
            gettimeofday(&tv, 0);

            t = (tv.tv_sec - this->_baseTime.tv_sec) +
                (tv.tv_usec - this->_baseTime.tv_usec) * 0.000001f;
            return t;
        }

#endif

    }
}

