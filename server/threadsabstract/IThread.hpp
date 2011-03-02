#ifndef __ITHREAD_HPP__
# define __ITHREAD_HPP__

#include "ThreadType.hpp"

namespace Gmgp
{
    namespace Server
    {

        /// Interface which provides easy manipulation of Thread both in
        /// Windows and Linux environment.
        class IThread
        {
            public:
                virtual ~IThread(void) {}

                /// Quits thread.
                virtual void Quit(void) = 0;

                /// Suspends execution of the calling thread until the target thread terminates
                virtual void Join(void) = 0;
        };

    }
}

#endif /* !__ITHREAD_HPP__ */

