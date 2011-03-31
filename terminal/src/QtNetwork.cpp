#ifndef _WIN32
    #include <arpa/inet.h>
#else
    #include <Winsock2.h>
#endif
#include "QtNetwork.hpp"
#include "Terminal.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        QtNetwork::QtNetwork(Terminal& term) :
            _term(term), _packetSize(0), _clientId(0), _bytesRemainingForSize(2)
        {
            this->_socket = new QTcpSocket(this);
            this->_socket->setTextModeEnabled(false);
            QObject::connect(this->_socket, SIGNAL(readyRead()), this, SLOT(_SocketReady()));
            QObject::connect(this->_socket, SIGNAL(connected()), this, SLOT(_SocketConnected()));
            QObject::connect(this->_socket, SIGNAL(disconnected()), this, SLOT(_SocketDisconnected()));
            QObject::connect(this->_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(_SocketError(QAbstractSocket::SocketError)));
            this->_packetManager = new TcpPacketManager(this->_term);
        }

        QtNetwork::~QtNetwork()
        {
            delete this->_socket;
        }

        uint16_t QtNetwork::GetClientId() const
        {
            return this->_clientId;
        }

        void QtNetwork::SetClientId(uint16_t clientId)
        {
            this->_clientId = clientId;
        }

        void QtNetwork::SendTcpPacket(Packet const& packet)
        {
            if (this->_socket->state() != QAbstractSocket::ConnectedState)
            {
                Log::W("Packet discarded: socket not ready yet.");
                return;
            }
            QByteArray bytes;
            QDataStream out(&bytes, QIODevice::WriteOnly);
            out.writeRawData(packet.GetCompleteData(), packet.GetCompleteSize());
            Log::D("TCP: Sending " + String(packet.GetCompleteSize()) + " bytes to " + this->_serverAddress.toString().toStdString() + ":" + String(this->_socket->peerPort()) + ".");
            this->_socket->write(bytes);
            this->_socket->flush();
        }

        void QtNetwork::Connect(String const& ip, unsigned short port)
        {
            this->_socket->connectToHost(ip.c_str(), port);
            _host = ip;
        }

        String const& QtNetwork::GetHost() const
        {
            return this->_host;
        }

        void QtNetwork::_SocketReady()
        {
            QDataStream in(this->_socket);

            if (this->_bytesRemainingForSize > 0)
            {
                this->_bytesRemainingForSize -= in.readRawData(reinterpret_cast<char*>(&this->_packetSize) +
                                                               (2 - this->_bytesRemainingForSize),
                                                               this->_bytesRemainingForSize);
                if (this->_bytesRemainingForSize == 0)
                {
                    this->_packetSize = ntohs(this->_packetSize);
                    this->_bytesRead = 0;
                    this->_data = new char[this->_packetSize];
                }
                else
                    return;
            }

            this->_bytesRead += in.readRawData(this->_data + this->_bytesRead,
                                               this->_packetSize - this->_bytesRead);

            if (this->_bytesRead == this->_packetSize)
            {
                Packet p;
                p.WriteData(this->_data, this->_packetSize);
                delete [] this->_data;
                this->_packetManager->ProcessPacket(p);

                this->_bytesRemainingForSize = 2;
                this->_SocketReady();
            }
        }

//        void QtNetwork::_SocketReady()
//        {
//            QDataStream in(this->_socket);
//
//            if (this->_packetSize == 0)
//            {
//                if (this->_socket->bytesAvailable() < 2)
//                    return;
//                uint16_t size;
//                in.readRawData(reinterpret_cast<char*>(&size), 2);
//                this->_packetSize = ntohs(size);
//            }
//
//            if (this->_socket->bytesAvailable() < this->_packetSize)
//            {
//                Log::D(String("Waiting for more data on TCP socket (total ") + this->_packetSize + " bytes).");
//                return ;
//            }
//
//            Log::D("TCP Packet of " + String(this->_packetSize) + " + 2 bytes received.");
//            char* data = new char[this->_packetSize];
//            in.readRawData(data, this->_packetSize);
//            Packet p;
//            p.WriteData(data, this->_packetSize);
//            delete [] data;
//            this->_packetManager->ProcessPacket(p);
//
//            this->_packetSize = 0;
//            if (this->_socket->bytesAvailable() > 0)
//                this->_SocketReady();
//        }

        void QtNetwork::_SocketConnected()
        {
            this->_serverAddress = this->_socket->peerAddress();
            this->_term.GetUpdaterWindow()->AddMessage("Connected to " + this->GetHost() + ".");
            this->_term.GetUpdaterWindow()->show();
            this->_term.GetConnectionWindow()->close();
            Packet p;
            p.Write8(Packet::ANYONE_THERE);
            p.WriteString("hallal_a = close");
            p.WriteString(this->_term.GetConnectionWindow()->GetNickname());
            this->SendTcpPacket(p);
            this->_term.GetUpdaterWindow()->AddMessage("Waiting for the server...");
        }

        void QtNetwork::_SocketDisconnected()
        {
        }

        void QtNetwork::_SocketError(QAbstractSocket::SocketError)
        {
            if (this->_term.GetGameView()->IsRunning())
                this->_term.GetGameView()->Stop();
            else
                this->_term.GetConnectionWindow()->EnableConnection(true);
            this->_term.InformUser(String("A connection error occurred:<br>") + String(this->_socket->errorString().toStdString()));
        }

    }
}

