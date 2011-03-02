
#include <stdexcept>
#include <iostream>

#include "Thread.hpp"
#include "Log.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

# ifdef _WIN32 // Windows

        Thread::Thread(FUNCTOR1(void) const & f) :
            _thread(0), _joined(false)
        {
            this->_functor = f;
            this->_thread = (Thread_t*)CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread::_Run), reinterpret_cast<LPVOID>(this), 0, 0);

        }

        Thread::~Thread()
        {
            if (!this->_joined)
                this->Quit();
        }

        void Thread::Join(void)
        {
            if (this->_thread != 0)
                WaitForSingleObject(this->_thread, INFINITE);
            this->_joined = true;
        }

        void Thread::Quit(void)
        {
            if (this->_thread != 0)
                TerminateThread(this->_thread, 0);
            this->_joined = true;
        }

# else // Unix

        Thread::Thread(FUNCTOR1(void) const &f) :
            _thread(0), _joined(false)
        {
            this->_thread = new Thread_t;
            this->_functor = f;

            if (pthread_create(this->_thread, 0, reinterpret_cast<void* (*)(void*)>(Thread::_Run), this) != 0)
                throw (std::runtime_error("pthread_create error."));
        }

        Thread::~Thread()
        {
            if (!this->_joined)
                pthread_detach(*this->_thread);
            if (this->_thread != 0)
                delete this->_thread;
        }

        void Thread::Join(void)
        {
            if (!this->_joined)
            {
                pthread_join(*this->_thread, 0);
                this->_joined = true;
            }
        }

        void Thread::Quit(void)
        {
            if (this->_thread == 0)
                return;
            pthread_exit(this->_thread);
        }

# endif

        void* Thread::_Run(Thread* t)
        {
            try
            {
#ifdef _WIN32
                // Windows have random seed for each threads
                ::srand(reinterpret_cast<size_t>(t));
#endif
                (t->_functor)();
            }
            catch (std::exception &e)
            {
                Log::E(String("Exception: ") + e.what());
                throw;
            }
            return (0);
        }

    }
}
