#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include <queue>
#include <vector>

#include "functor.hpp"
#include "IMutex.hpp"
#include "IThread.hpp"
#include "ThreadCondition.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ThreadPool
        {
        public:
            ThreadPool(unsigned int nbThreads = 8);
            ~ThreadPool(void);

            /// Queues a functor for execution. The functor executes when a thread pool thread becomes available.
            void QueueWorkItem(FUNCTOR1(void) const& workItem);

        private:
            bool _running;
            ThreadCondition *_condition;
            IMutex* _workItemsMutex;
            std::queue< FUNCTOR1(void) > _workItems;
            std::vector< IThread* > _threads;

            bool _HasWaitingWork(void);
            void _Run(void);
        };

    }
}

#endif
