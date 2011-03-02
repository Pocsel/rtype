#ifndef __TCPPACKETMANAGER_HPP__
#define __TCPPACKETMANAGER_HPP__

#include <map>
#include <QFile>
#include "INetwork.hpp"
#include "Terminal.hpp"
#include "Packet.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class TcpPacketManager
        {
            public:
                explicit TcpPacketManager(Terminal& term);
                ~TcpPacketManager();
                void ProcessPacket(Packet const& p);
            private:
                struct ResourceMetadata
                {
                    uint16_t id;
                    uint8_t type;
                    String path;
                    uint16_t frames;
                    uint16_t delay;
                    uint8_t isVertical;
                    uint8_t isMusic;
                    String functionName;
                    bool downloaded;
                };
                void _CheckForFinishedDownload();
                void _AddResource(ResourceMetadata* meta);
                void _RequestResources();
                void _PacketInGame(Packet const& p);
                void _PacketIHaveThis(Packet const& p);
                void _PacketPleaseComeIn(Packet const& p);
                void _PacketTakeIt(Packet const& p);
                void _PacketTakeSomeMore(Packet const& p);
                void _PacketWatchThisOut(Packet const& p);
                void _PacketPing(Packet const& p);
                typedef void (TcpPacketManager::*handlerMethod)(Packet const&);
                std::map<uint8_t, handlerMethod> _handlers;
                Terminal& _term;
                size_t _currentItem;
                size_t _totalItems;
                std::list<ResourceMetadata*> _resources;
                QFile _file;
                size_t _fileSize;
                bool _receivedWelcome;
                bool _receivedResources;
                bool _downloadingFinished;
        };

    }
}

#endif

