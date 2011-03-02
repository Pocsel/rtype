
#ifndef BASICGAME_HPP_
# define BASICGAME_HPP_

#include "IGame.hpp"
#include "Clock.hpp"
#include "EntityManager.hpp"
#include "PlayerManager.hpp"
#include "ResourceManager.hpp"
#include "ItemManager.hpp"
#include "Constants.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename Entity, typename Player>
            class BasicGame : public IGame
        {
        public:
            explicit BasicGame(String const& name, unsigned int frameDelay, unsigned int width, unsigned int height)
                : _running(false), _name(name), _frameDelay(frameDelay), _width(width), _height(height),
                _initialized(false), _serverProxy(0), _service(0)
            {
                this->_playerManager = new PlayerManager<Entity, Player>(*this);
                this->_entityManager = new EntityManager<Entity, Player>(*this);
                this->_resourceManager = new ResourceManager<Entity, Player>(*this);
                this->_itemManager = new ItemManager<Entity, Player>(*this);
            }

            ~BasicGame(void)
            {
                delete this->_playerManager;
                delete this->_entityManager;
                delete this->_itemManager;
                delete this->_resourceManager;
                if (this->_initialized)
                    delete this->_service;
            }

        public:

            void Run(void)
            {
                this->_PreRun();
                this->_service->RegisterTimer(this->_frameDelay, b00st::bind(&BasicGame<Entity, Player>::_Tick, *this));
                this->_service->RegisterTimer(945, b00st::bind(&BasicGame<Entity, Player>::_Ping, *this));
                this->_clock.Reset();
                this->_running = true;
                this->_service->Run();
                this->_running = false;
                this->_PostRun();
            }

        protected:
            virtual void _PreRun(void)
            {
            }

            virtual void _PostRun(void)
            {
            }

        public:
            bool Initialize(IServerProxy& serverProxy)
            {
                if (this->_initialized)
                {
                    Log::W(this->_name + ": game already initialized.");
                    return false;
                }
#ifdef DEBUG
                this->_debugCount = 0;
                this->_debugElapsedTime = 0;
#endif
                this->_serverProxy = &serverProxy;
                this->_InitializeResources();
                if (!this->_resourceManager->Load())
                    return false;
                this->_service = this->_serverProxy->GetService();
                this->_initialized = true;
                Log::I(this->_name + " initialized.");
                return true;
            }

        protected:
            virtual void _InitializeResources(void)
            {
            }

        public:
            void AddPlayer(uint16_t playerId, String const& nick, ITcpSocketProxy* socketProxy)
            {
                if (!this->_initialized)
                {
                    Log::W(this->_name + ": Cannot add player " + playerId + ": game not initialized.");
                    return;
                }
                Log::I(this->_name + ": Player " + String(playerId) + " entered the game.");
                this->_playerManager->AddPlayer(playerId, nick, socketProxy);
                this->_OnAddPlayer(playerId);
            }

        protected:
            virtual void _OnAddPlayer(uint16_t)
            {
            }

            virtual bool _Ping(uint32_t)
            {
                std::list<uint16_t> daList = this->_playerManager->GetPlayerIdList();
                for (std::list<uint16_t>::iterator it = daList.begin(), ite = daList.end() ; it != ite ; ++it)
                {
                    if (this->_playerManager->Ping(*it) == false)
                    {
                        Log::I("Not enuff PONG : player " + String(*it) + " has been kicked out.");
                        delete this->_playerManager->GetPlayer(*it).GetSocketProxy();
                        this->RemovePlayer(*it);
                    }
                }
                return false;
            }

        public:

            void MovePlayer(uint16_t playerId, IGame* game)
            {
                if (this->_playerManager->HasPlayer(playerId))
                {
                    Player* p = &this->_playerManager->GetPlayer(playerId);
                    String nick = p->GetNick();
                    ITcpSocketProxy* proxy = p->GetSocketProxy();

                    // "delete all"
                    Packet packet;
                    packet.Write8(Packet::IN_GAME);
                    packet.WriteFloat(0);
                    packet.Write8(0);
                    proxy->Send(packet);

                    this->RemovePlayer(playerId);
                    game->AddPlayer(playerId, nick, proxy);
                }
            }

            void RemovePlayer(uint16_t playerId)
            {
                if (!this->_initialized)
                {
                    Log::W(this->_name + ": Cannot remove player " + playerId + ": game not initialized.");
                    return;
                }
                Log::I(this->_name + ": Player " + playerId + " left the game.");
                this->_playerManager->RemovePlayer(playerId);
                this->_OnRemovePlayer(playerId);
            }

        protected:
            virtual void _OnRemovePlayer(uint16_t)
            {
            }

        public:
            void Stop(void)
            {
                if (this->_service == 0)
                    throw std::runtime_error("game not initialized yet");
                this->_service->Stop();
            }

            IServerProxy& GetServer()
            {
                if (this->_serverProxy == 0)
                    throw std::runtime_error("game not initialized yet");
                return *this->_serverProxy;
            }

            ResourceManager<Entity, Player>& GetResourceManager() {return *this->_resourceManager;}
            ItemManager<Entity, Player>& GetItemManager() {return *this->_itemManager;}
            PlayerManager<Entity, Player>& GetPlayerManager() {return *this->_playerManager;}
            EntityManager<Entity, Player>& GetEntityManager() {return *this->_entityManager;}
            String const& GetName(void) const {return this->_name;}
            float GetElapsedTime() {return this->_clock.GetElapsedTime();}
            float R() const {return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));}
            IService& GetService(void) {return *this->_service;}
            unsigned int GetWidth(void) const {return this->_width;}
            unsigned int GetHeight(void) const {return this->_height;}

        protected:
            bool _Tick(uint32_t)
            {
#ifdef DEBUG
                this->_debugClock.Reset();
                if (++this->_debugCount >= 200)
                {
                    this->_debugCount = 0;
                    Log::D(this->_name + ": one tick = " + this->_debugElapsedTime * 1000 / 200 + "ms.");
                    this->_debugElapsedTime = 0;
                }
#endif


              this->_entityManager->Run(this->_clock.GetElapsedTime());
              this->_itemManager->Run(this->_clock.GetElapsedTime());
              this->_playerManager->FlushEvents();


#ifdef DEBUG
                this->_debugElapsedTime += this->_debugClock.GetElapsedTime();
#endif
                return false;
            }

        protected:
            bool _running;

        private:
            PlayerManager<Entity, Player>* _playerManager;
            EntityManager<Entity, Player>* _entityManager;
            ResourceManager<Entity, Player>* _resourceManager;
            ItemManager<Entity, Player>* _itemManager;
            String _name;
            unsigned int _frameDelay;
            unsigned int _width;
            unsigned int _height;
            bool _initialized;
            IServerProxy* _serverProxy;
            IService* _service;
            Clock _clock;

#ifdef DEBUG
            int _debugCount;
            float _debugElapsedTime;
            Clock _debugClock;
#endif
        };

    }
}

#endif // !BASICGAME_HPP_
