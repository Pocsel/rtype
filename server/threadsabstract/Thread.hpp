#ifndef __THREAD_HPP__
# define __THREAD_HPP__

#include "IThread.hpp"
#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Thread : public IThread
        {
        public:

            /// Creates thread, taking FUNCTOR1 resulting from b00st::bind().
            Thread(FUNCTOR1(void)const & f);

            ~Thread(void);

            /// Quits thread.
            void Quit(void);

            /// Suspends execution of the calling thread until the target thread terminates
            void Join(void);

        private:
            Thread_t* _thread;
            bool _joined;
            static void* _Run(Thread* thread);
            FUNCTOR1(void) _functor;
        };

    }
}

#endif /* !__THREAD_HPP__ */

