
#ifndef ISERVICE_HPP_
# define ISERVICE_HPP_

#include "ITcpSocket.hpp"
#include "ITcpSocketProxy.hpp"
#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        /// IService :
        ///
        /// You register stuff on it, and it makes miracles happen
        ///
        /// If an error occurs on a socket / acceptor : the corresponding handler is it is removed from

        class IService
        {
        private:
            typedef FUNCTOR3(bool, int, ITcpSocket*) AcceptHandler;
            typedef FUNCTOR4(bool, int, char*, size_t) DataHandler;
            typedef FUNCTOR2(bool, uint32_t) TimerHandler;

        public:
            virtual ~IService(void) {}

            /// Methods from INetworkConnectionHandler classes will be called when :
            /// - a successful accept has been made
            /// - an error on a accept happened
            virtual void RegisterAcceptor(ITcpSocket& socket, AcceptHandler const& handler) = 0;

            /// Methods from INetworkDataHandler classes will be called when :
            /// - a successfull read has been made
            /// - an error on a read/write happened
            virtual ITcpSocketProxy& RegisterTcpSocket(ITcpSocket& socket, DataHandler const& handler) = 0;
            virtual void RegisterTcpSocket(ITcpSocketProxy* socket, DataHandler const& handler) = 0;

            virtual uint32_t RegisterTimer(uint32_t milliseconds, TimerHandler const& handler) = 0;
            virtual void UnregisterAcceptor(ITcpSocket const& socket) = 0;
            virtual ITcpSocketProxy* UnregisterTcpSocket(ITcpSocket const& socket) = 0;
            virtual void UnregisterTcpSocket(ITcpSocketProxy const* socket) = 0;
            virtual void UnregisterTimer(uint32_t timerId) = 0;
            virtual void Stop(void) = 0;
            virtual void Run(void) = 0;
        };

    }
}

#endif // !ISERVICE_HPP_
