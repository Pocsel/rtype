#ifndef __IMUTEX_HPP__
# define __IMUTEX_HPP__

#include "ThreadType.hpp"

namespace Gmgp
{
    namespace Server
    {

        class IMutex
        {
            public:
                virtual ~IMutex(void) {}

                virtual void Lock(void) = 0;
                virtual bool TryLock(void) = 0;
                virtual void UnLock(void) = 0;
        };

    }
}

#endif /* !__IMUTEX_HPP__ */

