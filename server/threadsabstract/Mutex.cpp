#include <stdexcept>
#include <iostream>
#include "Mutex.hpp"

namespace Gmgp
{
    namespace Server
    {

# ifdef _WIN32 // Windows

        Mutex::Mutex() : _locked(false)
        {
            this->_mutex = (Mutex_t*)CreateMutex(NULL, false, NULL); // TRUE = LOCK
        }

        Mutex::~Mutex()
        {
            CloseHandle(this->_mutex);
            this->_locked = false;
            ReleaseMutex(this->_mutex);
        }

        void Mutex::Lock(void)
        {
            WaitForSingleObject(this->_mutex, INFINITE);
            this->_locked = true;
        }

        bool Mutex::TryLock(void)
        {
            if (this->_locked)
                return false;
            DWORD res = WaitForSingleObject(this->_mutex, INFINITE);

            if (res == WAIT_ABANDONED)
                return false;
            this->_locked = true;
            return true;
        }

        void Mutex::UnLock(void)
        {
            ReleaseMutex(this->_mutex);
            this->_locked = false;
        }

# else // Unix

        Mutex::Mutex() : _locked(false)
        {
            this->_mutex = new Mutex_t;
            pthread_mutex_init(this->_mutex, NULL);
        }


        Mutex::~Mutex()
        {
            if (this->_locked)
                this->UnLock();
            if (pthread_mutex_destroy(this->_mutex) != 0)
                throw (std::runtime_error("pthread_mutex_destroy() failure"));
            if (this->_mutex != 0)
                delete this->_mutex;
        }

        void Mutex::Lock(void)
        {
            if (this->_locked)
                return;
            if (this->_mutex == 0 || pthread_mutex_lock(this->_mutex) != 0)
                throw (std::runtime_error("pthread_mutex_lock() failure"));
            this->_locked = true;
        }

        bool Mutex::TryLock(void)
        {
            if (this->_locked)
                return (false);
            if (this->_mutex == 0 || pthread_mutex_trylock(this->_mutex) != 0)
                return (false);
            this->_locked = true;
            return (true);
        }

        void Mutex::UnLock(void)
        {
            if (this->_mutex == 0 || pthread_mutex_unlock(this->_mutex) != 0)
                throw (std::runtime_error("pthread_mutex_unlock() failure"));
            this->_locked = false;
        }

# endif

    }
}
