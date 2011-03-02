#include <QDir>
#include <QFileInfo>
#include "Constants.hpp"
#include "Log.hpp"
#include "TcpPacketManager.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        TcpPacketManager::TcpPacketManager(Terminal& term) :
            _term(term), _currentItem(0), _totalItems(0), _fileSize(0), _receivedWelcome(false), _receivedResources(false), _downloadingFinished(false)
        {
            this->_handlers[Packet::PLEASE_COME_IN] = &Gmgp::Terminal::TcpPacketManager::_PacketPleaseComeIn;
            this->_handlers[Packet::I_HAVE_THIS] = &Gmgp::Terminal::TcpPacketManager::_PacketIHaveThis;
            this->_handlers[Packet::TAKE_IT] = &Gmgp::Terminal::TcpPacketManager::_PacketTakeIt;
            this->_handlers[Packet::TAKE_SOME_MORE] = &Gmgp::Terminal::TcpPacketManager::_PacketTakeSomeMore;
            this->_handlers[Packet::WATCH_THIS_OUT] = &Gmgp::Terminal::TcpPacketManager::_PacketWatchThisOut;
            this->_handlers[Packet::PING] = &Gmgp::Terminal::TcpPacketManager::_PacketPing;
            this->_handlers[Packet::IN_GAME] = &Gmgp::Terminal::TcpPacketManager::_PacketInGame;
        }

        TcpPacketManager::~TcpPacketManager()
        {
        }

        void TcpPacketManager::_AddResource(ResourceMetadata* meta)
        {
            if (meta->type == ANIMATION)
                this->_term.GetGameView()->AddAnimation(meta->id, meta->path, meta->frames, meta->delay, meta->isVertical);
            else if (meta->type == SOUND)
                this->_term.GetGameView()->AddSound(meta->id, meta->path, meta->isMusic);
            else if (meta->type == LUA)
                this->_term.GetGameView()->AddLua(meta->id, meta->path, meta->functionName);
            else
                Log::W("Cannot add resource " + meta->path + " to game view: unknown type.");
        }

        void TcpPacketManager::_CheckForFinishedDownload()
        {
            size_t done = 0;
            bool found = false;
            std::list<ResourceMetadata*>::iterator it = this->_resources.begin();
            std::list<ResourceMetadata*>::iterator itEnd = this->_resources.end();
            for (; it != itEnd; ++it)
                if ((*it)->downloaded)
                    ++done;
                else
                    found = true;
            this->_term.GetUpdaterWindow()->SetTotalBar(static_cast<float>(done) / static_cast<float>(this->_totalItems == 0 ? 1 : this->_totalItems) * 100);
            if (!found)
            {
                this->_downloadingFinished = true;
                this->_term.GetUpdaterWindow()->AddMessage("All " + String(this->_totalItems) + " resources are up to date.");
                this->_term.GetUpdaterWindow()->SetStatus("All your resources are up to date.");
                this->_term.GetUpdaterWindow()->EnablePlay(true);
                this->_term.GetUpdaterWindow()->SetCurrentBar(100);
            }
        }

        void TcpPacketManager::_RequestResources()
        {
            size_t requests = 0;
            this->_totalItems = 0;
            std::list<ResourceMetadata*>::iterator it = this->_resources.begin();
            std::list<ResourceMetadata*>::iterator itEnd = this->_resources.end();
            this->_term.GetUpdaterWindow()->AddMessage("Sending download requests...");
            this->_term.GetUpdaterWindow()->SetStatus("Requesting resources...");
            for (; it != itEnd; ++it)
            {
                ++this->_totalItems;
                if (!QFile::exists((*it)->path.c_str()))
                {
                    ++requests;
                    Packet req;
                    req.Write8(Packet::I_NEED_THIS);
                    req.Write16((*it)->id);
                    this->_term.GetNetwork()->SendTcpPacket(req);
                }
                else
                    (*it)->downloaded = true;
            }
            this->_term.GetUpdaterWindow()->AddMessage(String(requests) + " download requests sent.");
            this->_term.GetUpdaterWindow()->SetStatus("Downloading needed resources...");
            this->_CheckForFinishedDownload();
        }

        void TcpPacketManager::_PacketPing(Packet const& p)
        {
            Log::D("<Ping> packet received.");
            Packet rep;
            rep.Write8(Packet::PONG);
            rep.WriteString(p.ReadString());
            this->_term.GetNetwork()->SendTcpPacket(rep);
        }

        void TcpPacketManager::_PacketInGame(Packet const& p)
        {
            Log::D("<In Game> packet received.");
            this->_term.GetGameView()->PushData(p.GetData() + 1, p.GetSize() - 1);
        }

        void TcpPacketManager::_PacketWatchThisOut(Packet const& p)
        {
            Log::D("<Watch this out> packet received.");
            uint16_t resX = p.Read16();
            uint16_t resY = p.Read16();
            p.Read16(); // unused Port
            if (!this->_term.GetGameView()->IsRunning())
            {
                std::list<ResourceMetadata*>::iterator it = this->_resources.begin();
                std::list<ResourceMetadata*>::iterator itEnd = this->_resources.end();
                for (; it != itEnd; ++it)
                {
                    this->_AddResource(*it);
                    delete *it;
                }
                this->_resources.clear();
                this->_term.GetGameView()->Start();
                this->_term.GetUpdaterWindow()->hide();
            }
            this->_term.GetGameView()->SetResolution(resX, resY);
        }

        void TcpPacketManager::_PacketTakeIt(Packet const& p)
        {
            Log::D("<Take it> packet received.");
            if (this->_downloadingFinished)
            {
                Log::W("Packet ignored: all resources are already downloaded.");
                return;
            }
            if (this->_file.isOpen())
                this->_file.close();
            ResourceMetadata* meta = 0;
            uint16_t id = p.Read16();
            this->_fileSize = p.Read32();
            std::list<ResourceMetadata*>::iterator it = this->_resources.begin();
            std::list<ResourceMetadata*>::iterator itEnd = this->_resources.end();
            for (; it != itEnd; ++it)
                if ((*it)->id == id && !(*it)->downloaded)
                    meta = *it;
            if (meta != 0)
            {
                if (this->_file.isOpen())
                    this->_file.close();
                this->_file.setFileName(meta->path.c_str());
                QFileInfo info(this->_file);
                if (!QFile::exists(info.path()))
                {
                    QDir dir;
                    if (!dir.mkpath(info.path()))
                        Log::E("Could not create path " + info.path().toStdString() + ".");
                }
                this->_term.GetUpdaterWindow()->SetCurrentBar(0);
                if (!this->_file.open(QIODevice::WriteOnly))
                    Log::E("Could not open " + meta->path + " for writing.");
                else
                {
                    this->_currentItem = meta->id;
                    this->_term.GetUpdaterWindow()->AddMessage("Downloading " + meta->path + " (" + String(this->_fileSize) + " bytes)...");
                }
            }
            else
                Log::W("Resource " + String(id) + " is invalid, cannot download.");
        }

        void TcpPacketManager::_PacketIHaveThis(Packet const& p)
        {
            Log::D("<I have this> packet received.");
            if (this->_receivedResources)
            {
                Log::W("Packet ignored: all resources infomations already received.");
                return;
            }
            ResourceMetadata* meta = new ResourceMetadata;
            meta->downloaded = false;
            meta->id = p.Read16();
            meta->type = p.Read8();
            meta->path = "data/" + p.ReadString();
            if (meta->type == ANIMATION)
            {
                ++this->_currentItem;
                meta->frames = p.Read16();
                meta->delay = p.Read16();
                meta->isVertical = p.Read8();
                this->_term.GetUpdaterWindow()->AddMessage("[" + String(this->_currentItem) + "/" + String(this->_totalItems) + "] Resource " + String(meta->id) + ": animation file " + meta->path + ".");
                this->_resources.push_back(meta);
            }
            else if (meta->type == SOUND)
            {
                ++this->_currentItem;
                meta->isMusic = p.Read8();
                this->_term.GetUpdaterWindow()->AddMessage("[" + String(this->_currentItem) + "/" + String(this->_totalItems) + "] Resource " + String(meta->id) + ": sound file " + meta->path + ".");
                this->_resources.push_back(meta);
            }
            else if (meta->type == LUA)
            {
                ++this->_currentItem;
                meta->functionName = p.ReadString();
                this->_term.GetUpdaterWindow()->AddMessage("[" + String(this->_currentItem) + "/" + String(this->_totalItems) + "] Resource " + String(meta->id) + ": lua file " + meta->path + ".");
                this->_resources.push_back(meta);
            }
            else
                this->_term.GetUpdaterWindow()->AddMessage("Resource " + String(meta->id) + ": invalid type.");
            if (this->_currentItem == this->_totalItems)
            {
                this->_receivedResources = true;
                this->_term.GetUpdaterWindow()->AddMessage("Received all resources informations.");
                this->_RequestResources();
            }
        }

        void TcpPacketManager::_PacketTakeSomeMore(Packet const& p)
        {
            Log::D("<Take some more> packet received.");
            if (this->_downloadingFinished)
            {
                Log::W("Packet ignored: all resources are already downloaded.");
                return;
            }
            if (!this->_file.isOpen())
            {
                Log::W("Data not expected, discaring.");
                return;
            }
            Log::D("Writing " + String(p.GetSize() - 1) + " bytes to " + this->_file.fileName().toStdString() + ".");
            this->_file.write(p.GetData() + 1, p.GetSize() - 1); // offset discards packet type byte
            if (this->_file.pos() >= this->_fileSize)
            {
                this->_term.GetUpdaterWindow()->SetCurrentBar(100);
                this->_file.close();
                ResourceMetadata* meta = 0;
                std::list<ResourceMetadata*>::iterator it = this->_resources.begin();
                std::list<ResourceMetadata*>::iterator itEnd = this->_resources.end();
                for (; it != itEnd; ++it)
                    if ((*it)->id == this->_currentItem && !(*it)->downloaded)
                        meta = *it;
                if (meta != 0)
                    meta->downloaded = true;
                this->_CheckForFinishedDownload();
            }
            else
                this->_term.GetUpdaterWindow()->SetCurrentBar((static_cast<float>(this->_file.pos()) / static_cast<float>(this->_fileSize)) * 100);
        }

        void TcpPacketManager::_PacketPleaseComeIn(Packet const& p)
        {
            Log::D("<Please come in> packet received.");
            if (this->_receivedWelcome)
            {
                Log::W("Packet ignored: already received.");
                return;
            }
            uint16_t clientId = p.Read16();
            uint16_t itemCount = p.Read16();
            this->_term.GetNetwork()->SetClientId(clientId);
            this->_term.GetUpdaterWindow()->AddMessage("Your are client " + String(clientId) + ".");
            this->_term.GetUpdaterWindow()->AddMessage("The server has " + String(itemCount) + " resources.");
            this->_totalItems = itemCount;
            if (itemCount == 0)
            {
                this->_term.GetUpdaterWindow()->SetStatus("No downloading needed: the server has no resources.");
                this->_term.GetUpdaterWindow()->EnablePlay(true);
                this->_term.GetUpdaterWindow()->SetTotalBar(100);
                this->_term.GetUpdaterWindow()->SetCurrentBar(100);
                this->_term.GetUpdaterWindow()->AddMessage("No resources needed.");
            }
            else
                this->_term.GetUpdaterWindow()->SetStatus("Gathering resources informations...");
        }

        void TcpPacketManager::ProcessPacket(Packet const& p)
        {
            try
            {
                uint8_t type = p.Read8();
                if (this->_handlers.count(type) == 1)
                    (this->*_handlers[type])(p);
                else
                    Log::W("Invalid TCP packet type: " + String(type) + ".");
            }
            catch (std::exception& e)
            {
                Log::W("Malformed TCP packet received: " + String(e.what()) + ".");
            }
        }

    }
}

