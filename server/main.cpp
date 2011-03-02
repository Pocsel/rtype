
#include <cstdlib>
#include <iostream>

#include "String.hpp"
#include "Server.hpp"
#include "Log.hpp"
#include "functor.hpp"

#ifdef _WIN32 //windows

FUNCTOR1(void) StopHandler;

BOOL WINAPI ConsoleControlHandler(DWORD control)
{
    if (control == CTRL_C_EVENT || control == CTRL_BREAK_EVENT || control == CTRL_CLOSE_EVENT || control == CTRL_SHUTDOWN_EVENT)
    {
        StopHandler();
        return true;
    }
    else
    {
        return false;
    }
}

int main(int ac, char** av)
{
    try
    {
        if (ac < 2)
        {
            ::Gmgp::Log::E("Usage: server <port> [games directory]");
            return 1;
        }

        ::Gmgp::Server::Server* server = new ::Gmgp::Server::Server((ac > 2 ? av[2] : "games"), 6666, ::atoi(av[1]));

        StopHandler = ::b00st::bind(&::Gmgp::Server::Server::Stop, *server);
        SetConsoleCtrlHandler(ConsoleControlHandler, true);

        server->Run();

        delete server;
    }
    catch (std::exception& e)
    {
        ::Gmgp::Log::E("Exception: " + ::Gmgp::String(e.what()));
    }

    return 0;
}

#else //unix

#include "Thread.hpp"

#include <pthread.h>
#include <signal.h>

int main(int ac, char** av)
{
    try
    {
        if (ac < 2)
        {
            Gmgp::Log::E("Usage: server <port> [games directory]");
            return EXIT_FAILURE;
        }

        // Block all signals for background thread.
        ::sigset_t new_mask;
        ::sigfillset(&new_mask);
        ::sigset_t old_mask;
        ::pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

        // Run server in background thread.
        ::Gmgp::Server::Server* server = new ::Gmgp::Server::Server((ac > 2 ? av[2] : "games"), 6666, ::atoi(av[1]));
        ::Gmgp::Server::Thread t(b00st::bind(&::Gmgp::Server::Server::Run, *server));

        // Restore previous signals.
        ::pthread_sigmask(SIG_SETMASK, &old_mask, 0);

        // Wait for signal indicating time to shut down.
        ::sigset_t wait_mask;
        ::sigemptyset(&wait_mask);
        ::sigaddset(&wait_mask, SIGINT);
        ::sigaddset(&wait_mask, SIGQUIT);
        ::sigaddset(&wait_mask, SIGTERM);
        ::pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
        int sig = 0;
        ::sigwait(&wait_mask, &sig);

        // Stop the server.
        server->Stop();
        t.Join();
        delete server;
    }
    catch (std::exception& e)
    {
        ::Gmgp::Log::E("Exception: " + ::Gmgp::String(e.what()));
    }

    return EXIT_SUCCESS;
}

#endif
