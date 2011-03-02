
#ifndef SERVICE_HPP_
# define SERVICE_HPP_

#include <map>
#include <list>

#include "IService.hpp"
#include "ITcpSocket.hpp"
#include "Timer.hpp"
#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Service : public IService
        {
        private:
            typedef FUNCTOR3(bool, int, ITcpSocket*) AcceptHandler;
            typedef FUNCTOR4(bool, int, char*, size_t) DataHandler;
            typedef FUNCTOR2(bool, uint32_t) TimerHandler;
            enum { buffSize = 4096 };

        private:
#ifdef _WIN32 //windows
            enum errorCode
            {
                SELECT_ERROR = SOCKET_ERROR,
            };
#else //unix
            enum errorCode
            {
                SELECT_ERROR = -1,
            };
#endif

        public:
            Service(void);
            ~Service(void);

            virtual void RegisterAcceptor(ITcpSocket& socket, AcceptHandler const& handler);
            virtual ITcpSocketProxy& RegisterTcpSocket(ITcpSocket& socket, DataHandler const& handler);
            virtual void RegisterTcpSocket(ITcpSocketProxy* socket, DataHandler const& handler);
            virtual uint32_t RegisterTimer(uint32_t milliseconds, TimerHandler const& handler);
            virtual void UnregisterAcceptor(ITcpSocket const& socket);
            virtual ITcpSocketProxy* UnregisterTcpSocket(ITcpSocket const& socket);
            virtual void UnregisterTcpSocket(ITcpSocketProxy const* socket);
            virtual void UnregisterTimer(uint32_t timerId);
            virtual void Stop(void);
            virtual void Run(void);

        private:
            void _InitFdsets(void);
            void _InitTimeOut(void);
            void _Select(void);
            void _ExecSockets(void);
            void _ExecAcceptor(std::map<ITcpSocket*, AcceptHandler>::iterator& acceptor);
            void _ExecTcpSocket(std::map<ITcpSocketProxy*, DataHandler>::iterator& socket);
            void _ExecTimers(void);
            void _CleanMaps(void);

            std::map<ITcpSocket*, AcceptHandler> _acceptors;
            std::map<ITcpSocketProxy*, DataHandler> _tcpSockets;
            std::map<uint32_t, Timer> _timers;
            uint32_t _nextTimerId;

            bool _running;
            fd_set _readFdset;
            fd_set _writeFdset;
            SocketFD _maxFd;
            struct timeval _timeOut;
            std::list<ITcpSocket*> _removedAcceptors;
            std::list<ITcpSocketProxy*> _removedTcpSockets;
            std::list<uint32_t> _removedTimers;
            char* _rdBuff;
        };

    }
}

#endif // !ISERVICE_HPP_
