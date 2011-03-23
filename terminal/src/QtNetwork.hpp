#ifndef __QTNETWORK_HPP__
#define __QTNETWORK_HPP__

#include <QTcpSocket>
#include <QUdpSocket>

#include "INetwork.hpp"
#include "TcpPacketManager.hpp"

namespace Gmgp
{
    namespace Terminal
    {
        class Terminal;
        class QtNetwork :
            public QObject, public INetwork
        {
            Q_OBJECT
            public:
                explicit QtNetwork(Terminal& term);
                ~QtNetwork();
                void Connect(String const& ip, unsigned short port);
                String const& GetHost() const;
                void SendTcpPacket(Packet const& packet);
                uint16_t GetClientId() const;
                void SetClientId(uint16_t clientId);
            private slots:
                void _SocketReady();
                void _SocketConnected();
                void _SocketDisconnected();
                void _SocketError(QAbstractSocket::SocketError error);
            private:
                Terminal& _term;
                QTcpSocket* _socket;
                uint16_t _packetSize;
                String _host;
                QHostAddress _serverAddress;
                TcpPacketManager* _packetManager;
                uint16_t _clientId;

                size_t _bytesRemainingForSize;
                size_t _bytesRead;
                char* _data;
        };
    }
}

#endif

