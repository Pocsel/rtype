#ifdef _WIN32 //windows
#include <windows.h>
#else //unix
#include <stdexcept>
#include <pthread.h>
#endif

#include "ThreadCondition.hpp"

namespace Gmgp
{
    namespace Server
    {

#ifdef _WIN32 //windows

        ThreadCondition::ThreadCondition(FUNCTOR1(bool) const& waitCondition)
        {
            this->_waitCondition = waitCondition;
            ::InitializeConditionVariable(&this->_condition);
            ::InitializeCriticalSection(&this->_critSect);
        }

        ThreadCondition::~ThreadCondition(void)
        {
            ::DeleteCriticalSection(&this->_critSect);
        }

        void ThreadCondition::Wait(void)
        {
            ::EnterCriticalSection(&this->_critSect);
            while (!(this->_waitCondition)())
                ::SleepConditionVariableCS(&this->_condition, &this->_critSect, INFINITE);
            ::LeaveCriticalSection(&this->_critSect);
        }

        void ThreadCondition::Wake(void)
        {
            ::EnterCriticalSection(&this->_critSect);
            if ((this->_waitCondition)())
                ::WakeConditionVariable(&this->_condition);
            ::LeaveCriticalSection(&this->_critSect);
        }

        void ThreadCondition::WakeAll(void)
        {
            ::WakeAllConditionVariable(&this->_condition);
        }

#else //unix

        ThreadCondition::ThreadCondition(FUNCTOR1(bool) const& waitCondition)
            : _waitCondition(waitCondition)
        {
            pthread_cond_init(&this->_condition, 0);
            pthread_mutex_init(&this->_mutex, 0);
        }

        ThreadCondition::~ThreadCondition(void)
        {
            ::pthread_cond_destroy(&this->_condition);
            if (::pthread_mutex_destroy(&this->_mutex) != 0)
                throw (std::runtime_error("pthread_mutex_destroy() failure"));
        }

        void ThreadCondition::Wait(void)
        {
            ::pthread_mutex_lock(&this->_mutex);
            while (!(this->_waitCondition)())
                ::pthread_cond_wait(&this->_condition, &this->_mutex);
            ::pthread_mutex_unlock(&this->_mutex);
        }

        void ThreadCondition::Wake(void)
        {
            ::pthread_mutex_lock(&this->_mutex);
            while ((this->_waitCondition)())
                ::pthread_cond_signal(&this->_condition);
            ::pthread_mutex_unlock(&this->_mutex);
        }

        void ThreadCondition::WakeAll(void)
        {
            ::pthread_cond_broadcast(&this->_condition);
        }

#endif

    }
}

/* Testing part:
static int count = 0;
void TestWorking(void)
{
#ifdef _WIN32
::Sleep(1000);
#else
::sleep(1);
#endif
Log::I(Gmgp::String(count++) + "\n");
}

int main(int, char**)
{
{
// Create 64 threads
Gmgp::Server::ThreadPool tp(64);

// Add work !
for (int i = 0; i < 1000; ++i)
tp.QueueWorkItem(b00st::bind(TestWorking));

// Don't destroy ThreadPool if isn't finished !!!!
while (count < 1000)
#ifdef _WIN32
::Sleep(100);
#else
::usleep(100000);
#endif
}
Log::I("Press enter to quit");
::getchar();
return 0;
}
 */
