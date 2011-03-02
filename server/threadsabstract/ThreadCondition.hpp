
#ifndef __THREADCONDITION_HPP__
#define __THREADCONDITION_HPP__

#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ThreadCondition
        {
        public:
            /// Constructs a ThreadCondition with waiting condition functor
            ThreadCondition(FUNCTOR1(bool) const& waitCondition);

            /// Destroys this ThreadCondition
            ~ThreadCondition(void);

            /// Waits condition's change
            void Wait(void);

            /// Wakes one waiting thread
            void Wake(void);

            /// Wakes all waiting threads
            void WakeAll(void);

        private:
            FUNCTOR1(bool) _waitCondition;
#ifdef _WIN32
            CONDITION_VARIABLE _condition;
            CRITICAL_SECTION _critSect;
#else
            pthread_cond_t _condition;
            pthread_mutex_t _mutex;
#endif
        };

    }
}

#endif /* !__THREADCONDITION_HPP__ */

