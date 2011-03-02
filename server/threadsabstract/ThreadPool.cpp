
#include "Mutex.hpp"
#include "ScopeLock.hpp"
#include "Thread.hpp"
#include "ThreadPool.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {


        ThreadPool::ThreadPool(unsigned int nbThreads)
            : _running(true), _workItems(), _threads(nbThreads)
        {
            this->_condition = new ThreadCondition(b00st::bind<bool>(&ThreadPool::_HasWaitingWork, *this));
            this->_workItemsMutex = new Mutex();
            for (unsigned int i = 0; i < nbThreads; ++i)
                this->_threads[i] = new Thread(b00st::bind(&ThreadPool::_Run, *this));
        }

        ThreadPool::~ThreadPool(void)
        {
            this->_running = false;
            this->_condition->WakeAll();
            for (unsigned int i = 0; i < this->_threads.size(); ++i)
            {
                this->_threads[i]->Join();
                delete this->_threads[i];
            }
            delete this->_workItemsMutex;
            delete this->_condition;
        }

        void ThreadPool::QueueWorkItem(FUNCTOR1(void) const& workItem)
        {
            ScopeLock sl(*this->_workItemsMutex);
            this->_workItems.push(workItem);
            this->_condition->Wake();
        }

        bool ThreadPool::_HasWaitingWork(void)
        {
            if (this->_running)
                return true;
            ScopeLock sl(*this->_workItemsMutex);
            return !(this->_workItems.empty());
        }

        void ThreadPool::_Run(void)
        {
            while (this->_running)
            {
                this->_condition->Wait();
                if (!this->_running)
                    break;

                FUNCTOR1(void) work;
                {
                    ScopeLock sl(*this->_workItemsMutex);
                    if (this->_workItems.empty())
                        continue;
                    work = this->_workItems.front();
                    this->_workItems.pop();
                }
                work();
            }
            Log::D(String("ThreadPool: Thread quit - running: ") + this->_running);
        }

    }
}
