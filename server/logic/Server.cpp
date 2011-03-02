
#include <fstream>
#include <iostream>
#include <cstring>

#include <sys/stat.h>
#include <time.h>

#include "Server.hpp"
#include "TcpSocket.hpp"
#include "Service.hpp"
#include "Log.hpp"
#include "Thread.hpp"
#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        Server::Server(String const& gamesPath, uint16_t, uint16_t port, uint32_t address)
            : _gamesPath(gamesPath), _service(new Service),
            _nextResourceId(1), _nextClientId(1), _nextGameId(1), _firstGameId(0)
        {
            ::srand(::time(NULL));

            this->_serverProxy = new ServerProxy(*this);
            this->_LoadGames();

            this->_acceptor = new TcpSocket(HostAddress(port, address));
            this->_service->RegisterAcceptor(*this->_acceptor, b00st::bind(&Server::_AcceptHandler, *this));
            this->_pingTimerId = this->_service->RegisterTimer(911, b00st::bind(&Server::_PingHandler, *this));
        }

        Server::~Server(void)
        {
            Log::I("Deleting resource informations...");
            for (std::map<uint16_t, AResourceInfo*>::iterator it = this->_resources.begin(),
                 ite = this->_resources.end() ; it != ite ; ++it)
                delete (*it).second;

            Log::I("Deleting clients...");
            for (std::map<uint16_t, Client*>::iterator it = this->_clients.begin(),
                 ite = this->_clients.end() ; it != ite ; ++it)
            {
                delete this->_service->UnregisterTcpSocket(it->second->GetSocket());
                delete (*it).second;
            }

            Log::I("Deleting games...");
            for (std::map<uint16_t, IGame*>::iterator it = this->_games.begin(),
                 ite = this->_games.end() ; it != ite ; ++it)
            {
                delete it->second;
                delete this->_gameThreads[it->first];
            }

            Log::I("Deleting libraries...");
            for (std::vector<DLHandler*>::iterator it = this->_libs.begin(),
                 ite = this->_libs.end() ; it != ite ; ++it)
                delete *it;

            Log::I("Deleting TCP stuff..");
            delete this->_serverProxy;
            delete this->_service;
            delete this->_acceptor;
        }

        void Server::Run(void)
        {
            Log::I("Server Started");
            this->_RunGames();

            this->_service->Run();
            Log::I("Server Stopped");

            Log::I("Stopping Games...");
            for (std::map<uint16_t, IGame*>::iterator it = this->_games.begin(),
                 ite = this->_games.end() ; it != ite ; ++it)
            {
                Log::I("Stopping: " + it->second->GetName());
                (*it).second->Stop();
                this->_gameThreads[it->first]->Join();
            }

        }

        void Server::Stop(void)
        {
            this->_service->Stop();
        }

        void Server::_LoadGames(void)
        {
            String confFile = this->_gamesPath + "/list.txt";
            Log::I("Loading GameList file.");
            std::ifstream i(confFile.c_str());
            if (i.is_open() == false)
                throw std::runtime_error("could not open games list file");

            char buff[4096];
            while (i.eof() == false)
            {
                i.getline(buff, 4096);
                if (buff[0] == '\0')
                    continue;
                String gamePath = this->_gamesPath + "/" + buff;

                Log::I("Loading " + String(buff));
                try
                {
                    this->_libs.push_back(new DLHandler(gamePath));
                    IGame* game = reinterpret_cast<IGame* (*)(void)>(this->_libs.back()->GetDLSym("GetGameInstance"))();
                    this->_games[this->_nextGameId++] = game;
                    Log::I("game loaded: " + game->GetName());
                    if (this->_firstGameId == 0)
                        this->_firstGameId = this->_nextGameId - 1;
                }
                catch (std::exception& e)
                {
                    Log::E("DL Load exception: " + String(e.what()));
                    Log::E("Could not load " + String(buff));
                }
            }

            if (this->_games.empty())
                throw std::runtime_error("Not a single game loaded!");

            std::list<uint16_t> destroyThem;

            for (std::map<uint16_t, IGame*>::iterator it = this->_games.begin(),
                 ite = this->_games.end() ; it != ite ; ++it)
            {
                Log::I("Initializing " + it->second->GetName());
                if (it->second->Initialize(*this->_serverProxy) == false)
                {
                    destroyThem.push_back(it->first);
                    if (it->first == this->_firstGameId)
                        throw std::runtime_error("Could not initialize the main menu...");
                }
            }

            for (std::list<uint16_t>::iterator it = destroyThem.begin(),
                 ite = destroyThem.end() ; it != ite ; ++it)
            {
                delete this->_games[*it];
                this->_games.erase(*it);
            }

            Log::I("Games are initialized!");

        }

        void Server::_RunGames(void)
        {
            Log::I("Starting games...");
            for (std::map<uint16_t, IGame*>::iterator it = this->_games.begin(),
                 ite = this->_games.end() ; it != ite ; ++it)
            {
                Log::I("Starting " + it->second->GetName());
                this->_gameThreads[it->first] = new Thread(b00st::bind(&IGame::Run, *it->second));
            }
            Log::I("Games started");
        }

        IService* Server::GetService(void) const
        {
            return new Service;
        }

        std::map<uint16_t, IGame*> const& Server::GetGameList(void)
        {
            return this->_games;
        }

        void Server::RegisterResource(AResourceInfo& infos)
        {
            String const& path = infos.GetPath();
            {
                std::ifstream i(String(this->_gamesPath + "/" + path).c_str());
                if (i.is_open() == false)
                    throw std::runtime_error("No Resource");
            }
            uint16_t id = this->_nextResourceId++;
            infos.SetId(id);
            this->_resources[id] = infos.Clone();
        }

        std::ifstream* Server::GetFile(uint16_t resourceId, size_t& size)
        {
            if (this->_resources.find(resourceId) == this->_resources.end())
                return 0;
            std::ifstream* i = new std::ifstream;
            i->open(String(this->_gamesPath + "/" + this->_resources[resourceId]->GetPath()).c_str(), std::ios::binary);
            if (i->is_open() == false)
            {
                delete i;
                return 0;
            }
            struct ::stat s;
            if (::stat(String(this->_gamesPath + "/" + this->_resources[resourceId]->GetPath()).c_str(), &s) == -1)
            {
                delete i;
                return 0;
            }
            size = s.st_size;
            return i;
        }

        std::map<uint16_t, AResourceInfo*> const& Server::GetResources(void) const
        {
            return this->_resources;
        }

        void Server::RemoveClient(uint16_t id)
        {
            if (this->_clients.find(id) != this->_clients.end())
                this->_clients.erase(id);
        }

        void Server::PutClientIngame(Client* client, ITcpSocketProxy* socketProxy)
        {
            this->_games[this->_firstGameId]->AddPlayer(client->GetId(), client->GetNick(), socketProxy);
        }

        bool Server::_AcceptHandler(int errorId, ITcpSocket* nuSocket)
        {
            Log::I("A new client arrived!");
            if (errorId == -1)
            {
                Log::W("Accept FlailuRLE !!!");
                return true;
            }
            this->_clients[this->_nextClientId] = new Client(nuSocket, this->_service, *this, this->_nextClientId);
            ++this->_nextClientId;
            return false;
        }

        bool Server::_PingHandler(uint32_t)
        {
            std::list<uint16_t> removableList;

            for (std::map<uint16_t, Client*>::iterator it = this->_clients.begin(),
                 ite = this->_clients.end() ; it != ite ; ++it)
            {
                Client* client = it->second;
                if (client->DidPong() == false)
                {
                    Log::I("Client kicked (no ping response): " + client->GetNick());
                    delete this->_service->UnregisterTcpSocket(client->GetSocket());
                    removableList.push_front(it->first);
                }
                else
                    client->Ping();
            }

            for (std::list<uint16_t>::iterator it = removableList.begin(),
                 ite = removableList.end() ; it != ite ; ++it)
            {
                delete this->_clients[*it];
                this->_clients.erase(*it);
            }

            return false;
        }

    }
}
