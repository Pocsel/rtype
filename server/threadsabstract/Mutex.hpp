#ifndef __MUTEX_HPP__
# define __MUTEX_HPP__

#include "IMutex.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Mutex : public IMutex
        {
            private:
                Mutex_t* _mutex;
                bool _locked;
            public:
                Mutex(void);
                ~Mutex(void);
                void Lock(void);
                bool TryLock(void);
                void UnLock(void);
        };

    }
}

#endif /* !__MUTEX_HPP__ */

