
#ifndef __SERVER_HPP__
# define __SERVER_HPP__

#include <map>
#include <fstream>

#include "String.hpp"
#include "Client.hpp"
#include "IGame.hpp"
#include "IService.hpp"
#include "DLHandler.hpp"
#include "AResourceInfo.hpp"
#include "ServerProxy.hpp"
#include "IThread.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Server
        {
        public:
            Server(String const& gamesPath, uint16_t unused_Port,
                   uint16_t port, uint32_t address = 0);
            ~Server(void);

            void Run(void);
            void Stop(void);
            IService* GetService(void) const;
            std::map<uint16_t, IGame*> const& GetGameList(void);
            void RegisterResource(AResourceInfo& infos);
            std::ifstream* GetFile(uint16_t resourceId, size_t& size);
            std::map<uint16_t, AResourceInfo*> const& GetResources(void) const;
            void RemoveClient(uint16_t id);
            void PutClientIngame(Client* client, ITcpSocketProxy* socketProxy);

        private:
            void _LoadGames(void);
            void _RunGames(void);
            bool _AcceptHandler(int errorId, ITcpSocket* nuSocket);
            bool _PingHandler(uint32_t timerId);

            String _gamesPath;
            IServerProxy* _serverProxy;
            IService* _service;
            ITcpSocket* _acceptor;
            uint32_t _pingTimerId;

            std::vector<DLHandler*> _libs;

            std::map<uint16_t, AResourceInfo*> _resources;
            uint16_t _nextResourceId;

            std::map<uint16_t, Client*> _clients;
            uint16_t _nextClientId;

            std::map<uint16_t, IGame*> _games;
            uint16_t _nextGameId;
            uint16_t _firstGameId;
            std::map<uint16_t, IThread*> _gameThreads;
        };

    }
}

#endif

