
#ifndef SCOPELOCK_HPP_
# define SCOPELOCK_HPP_

#include "IMutex.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ScopeLock
        {
        public:
            explicit inline ScopeLock(IMutex& mutex) : _mutex(mutex)
            {
                this->_mutex.Lock();
            }

            inline ~ScopeLock(void)
            {
                this->_mutex.UnLock();
            }

        private:
            IMutex& _mutex;
        };

    }
}

#endif // !SCOPELOCK_HPP_
