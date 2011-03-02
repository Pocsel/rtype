#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__

#include "NonCopyable.hpp"
#include "BasicGame.hpp"
#include "AResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename Entity, typename Player>
        class ResourceManager : private b00st::NonCopyable
        {
        public:

        ResourceManager(BasicGame<Entity, Player>& game) : _game(game)
        {
        }

        ~ResourceManager()
        {
            std::map<int, AResourceInfo*>::iterator it = this->_resources.begin();
            std::map<int, AResourceInfo*>::iterator itEnd = this->_resources.end();
            for (; it != itEnd; ++it)
                delete it->second;
        }

        std::map<int, AResourceInfo*> const& GetResources() const
        {
            return this->_resources;
        }

        bool Load()
        {
            try
            {
                std::map<int, AResourceInfo*>::iterator it = this->_resources.begin();
                std::map<int, AResourceInfo*>::iterator itEnd = this->_resources.end();
                for (; it != itEnd; ++it)
                {
                    Log::D(this->_game.GetName() + ": Registering " + it->second->GetPath());
                    this->_game.GetServer().RegisterResource(*it->second);
                }
            }
            catch (std::exception& e)
            {
                Log::E(this->_game.GetName() + ": Could not load all resources: " + String(e.what()));
                return false;
            }
            Log::I(this->_game.GetName() + ": All Resources Registered!");
            return true;
        }

        void RegisterResource(int localId, AResourceInfo* resourceInfo)
        {
            this->_resources[localId] = resourceInfo;
        }

        uint16_t GetResourceId(int id)
        {
            if (this->_resources.count(id) != 1)
            {
                Log::W(this->_game.GetName() + ": Cannot find resource " + String(id) + ".");
                return 0;
            }
            return this->_resources[id]->GetId();
        }

        void CopyResources(std::map<int, AResourceInfo*> const& resources)
        {
            std::map<int, AResourceInfo*>::const_iterator it = resources.begin();
            std::map<int, AResourceInfo*>::const_iterator itEnd = resources.end();
            for (; it != itEnd; ++it)
                this->_resources[it->first] = it->second->Clone();
        }

        private:
            BasicGame<Entity, Player>& _game;
            std::map<int, AResourceInfo*> _resources;
        };

    }
}

#endif

