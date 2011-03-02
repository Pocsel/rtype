
#include <cerrno>

#include "TcpSocketProxy.hpp"
#include "Service.hpp"
#include "TcpSocket.hpp"

namespace Gmgp
{
    namespace Server
    {

        Service::Service(void) : _nextTimerId(0), _running(false)
        {
            FD_ZERO(&this->_readFdset);
            FD_ZERO(&this->_writeFdset);
            this->_rdBuff = new char[buffSize];
        }

        Service::~Service(void)
        {
            delete[] this->_rdBuff;
        }

        void Service::RegisterAcceptor(ITcpSocket& socket, AcceptHandler const& handler)
        {
            this->_acceptors[&socket] = handler;
        }

        ITcpSocketProxy& Service::RegisterTcpSocket(ITcpSocket& socket, DataHandler const& handler)
        {
            TcpSocketProxy* nuProxy = new TcpSocketProxy(socket);
            this->_tcpSockets[nuProxy] = handler;
            return *nuProxy;
        }

        void Service::RegisterTcpSocket(ITcpSocketProxy* socket, DataHandler const& handler)
        {
            this->_tcpSockets[socket] = handler;
        }

        uint32_t Service::RegisterTimer(uint32_t milliseconds, TimerHandler const& handler)
        {
            this->_timers[++this->_nextTimerId] = Timer(milliseconds, Timer::GetTime(), handler);
            return this->_nextTimerId;
        }

        void Service::UnregisterAcceptor(ITcpSocket const& socket)
        {
            this->_acceptors.erase(&const_cast<ITcpSocket&>(socket));
        }

        ITcpSocketProxy* Service::UnregisterTcpSocket(ITcpSocket const& socket)
        {
            for (std::map<ITcpSocketProxy*, DataHandler>::iterator it = this->_tcpSockets.begin(),
                 ite = this->_tcpSockets.end() ; it != ite ; ++it)
            {
                if (&(it->first->GetSocket()) == &socket)
                {
                    ITcpSocketProxy* ssss = it->first;
                    this->_tcpSockets.erase(ssss);
                    return ssss;
                }
            }
            return 0;
        }

        void Service::UnregisterTcpSocket(ITcpSocketProxy const* socketProxy)
        {
            this->_tcpSockets.erase(const_cast<ITcpSocketProxy*>(socketProxy));
        }

        void Service::UnregisterTimer(uint32_t timerId)
        {
            this->_timers.erase(timerId);
        }

        void Service::Stop(void)
        {
            this->_running = false;
        }

        void Service::Run(void)
        {
            this->_running = true;
            while (this->_running)
            {
                this->_InitFdsets();
                this->_InitTimeOut();
                this->_Select();
                this->_ExecSockets();
                this->_ExecTimers();
                this->_CleanMaps();
            }
        }

        void Service::_InitFdsets(void)
        {
            FD_ZERO(&this->_readFdset);
            FD_ZERO(&this->_writeFdset);
            this->_maxFd = 0;

            SocketFD fd;

            // Acceptors
            for (std::map<ITcpSocket*, AcceptHandler>::iterator it = this->_acceptors.begin(),
                 ite = this->_acceptors.end() ; it != ite ; ++it)
            {
                fd = it->first->GetSocketFD();
                FD_SET(fd, &this->_readFdset);
                if (fd > this->_maxFd)
                    this->_maxFd = fd;
            }

            // Tcp sockets
            for (std::map<ITcpSocketProxy*, DataHandler>::iterator it = this->_tcpSockets.begin(),
                 ite = this->_tcpSockets.end() ; it != ite ; ++it)
            {
                fd = it->first->GetSocket().GetSocketFD();
                FD_SET(fd, &this->_readFdset);
                if (it->first->HasSomethingToSend())
                    FD_SET(fd, &this->_writeFdset);
                if (fd > this->_maxFd)
                    this->_maxFd = fd;
            }

        }

        void Service::_InitTimeOut(void)
        {
            uint32_t curTimeOut = 0;
            uint64_t curTime = Timer::GetTime();

            uint64_t longTime;
            uint32_t nuTimeOut;

            for (std::map<uint32_t, Timer>::iterator it = this->_timers.begin(),
                 ite = this->_timers.end() ; it != ite ; ++it)
            {
                longTime = it->second.lastOccur + it->second.delay;
                if (longTime < curTime)
                    curTimeOut = 1;
                else
                {
                    nuTimeOut = longTime - curTime;
                    if (nuTimeOut < curTimeOut || curTimeOut == 0)
                        curTimeOut = nuTimeOut;
                }
            }

            this->_timeOut.tv_sec = curTimeOut / 1000;
            this->_timeOut.tv_usec = (curTimeOut % 1000) * 1000;
        }

        void Service::_Select(void)
        {
            if (select(this->_maxFd + 1, &this->_readFdset, &this->_writeFdset, 0,
                       ((this->_timeOut.tv_sec || this->_timeOut.tv_usec) ? &this->_timeOut : 0)
                      ) == SELECT_ERROR)
            {
                if (errno != EINTR)
                    throw std::runtime_error("selecta flailurle");
            }
        }

        void Service::_ExecAcceptor(std::map<ITcpSocket*, AcceptHandler>::iterator& acceptor)
        {
            if (FD_ISSET(acceptor->first->GetSocketFD(), &this->_readFdset))
            {
                ITcpSocket* newSocket;
                try
                {
                    newSocket = acceptor->first->Accept();
                    if (acceptor->second(0, newSocket))
                    {
                        this->_removedAcceptors.push_front(acceptor->first);
                        return;
                    }
                }
                catch (std::exception&)
                {
                    if (acceptor->second(-1, static_cast<ITcpSocket*>(0)))
                        this->_removedAcceptors.push_front(acceptor->first);
                }
            }
        }

        void Service::_ExecTcpSocket(std::map<ITcpSocketProxy*, DataHandler>::iterator& socket)
        {
            if (FD_ISSET(socket->first->GetSocket().GetSocketFD(), &this->_readFdset))
            {
                ssize_t len = socket->first->GetSocket().Recv(this->_rdBuff, buffSize);
                if (len <= 0)
                {
                    if (socket->second(-1, reinterpret_cast<char*>(0), 0lu))
                        this->_removedTcpSockets.push_front(socket->first);
                    return;
                }
                size_t l = len;
                if (socket->second(0, this->_rdBuff, l))
                {
                    this->_removedTcpSockets.push_front(socket->first);
                    return;
                }
            }
            if (FD_ISSET(socket->first->GetSocket().GetSocketFD(), &this->_writeFdset))
            {
                if (socket->first->SendOnNetwork() < 0)
                    if (socket->second(-1, reinterpret_cast<char*>(0), 0lu))
                        this->_removedTcpSockets.push_front(socket->first);
            }
        }

        void Service::_ExecSockets(void)
        {
            // Acceptors
            for (std::map<ITcpSocket*, AcceptHandler>::iterator it = this->_acceptors.begin(),
                 ite = this->_acceptors.end() ; it != ite ; ++it)
                this->_ExecAcceptor(it);

            // Tcp sockets
            for (std::map<ITcpSocketProxy*, DataHandler>::iterator it = this->_tcpSockets.begin(),
                 ite = this->_tcpSockets.end() ; it != ite ; ++it)
                this->_ExecTcpSocket(it);

        }

        void Service::_ExecTimers(void)
        {
            uint64_t curTime = Timer::GetTime();
            for (std::map<uint32_t, Timer>::iterator it = this->_timers.begin(),
                 ite = this->_timers.end() ; it != ite ; ++it)
            {
                if (it->second.lastOccur + it->second.delay <= curTime)
                {
                    it->second.lastOccur += it->second.delay;
                    if (it->second.handler(it->first))
                        this->_removedTimers.push_front(it->first);
                }
            }
        }

        void Service::_CleanMaps(void)
        {
            for (std::list<ITcpSocket*>::const_iterator it = this->_removedAcceptors.begin(),
                 ite = this->_removedAcceptors.end() ; it != ite ; ++it)
                this->UnregisterAcceptor(**it);
            this->_removedAcceptors.clear();

            for (std::list<ITcpSocketProxy*>::const_iterator it = this->_removedTcpSockets.begin(),
                 ite = this->_removedTcpSockets.end() ; it != ite ; ++it)
                this->UnregisterTcpSocket(*it);
            this->_removedTcpSockets.clear();

            for (std::list<uint32_t>::const_iterator it = this->_removedTimers.begin(),
                 ite = this->_removedTimers.end() ; it != ite ; ++it)
                this->UnregisterTimer(*it);
            this->_removedTimers.clear();
        }

    }
}
