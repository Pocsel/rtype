#ifndef __ENTITYMANAGER_HPP__
#define __ENTITYMANAGER_HPP__

#include <list>

#include "InteractionManager.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {
        template<typename Entity, typename Player> class BasicGame;

        template<typename Entity, typename Player>
            class EntityManager : private b00st::NonCopyable
        {
        public:
            explicit EntityManager(BasicGame<Entity, Player>& game) :
                _game(game), _interactionManager(640, 480, 4)
            {
            }

            ~EntityManager()
            {
                this->_ProcessRegisterPool();
                this->_ProcessUnregisterPool();

                while (this->_entities.size())
                {
                    delete this->_entities.front();
                    this->_entities.pop_front();
                    this->_ProcessRegisterPool();
                    this->_ProcessUnregisterPool();
                }
            }

            void RegisterEntity(Entity* entity)
            {
                this->_registerPool.push_back(entity);
            }

            void UnregisterEntity(Entity* entity)
            {
                this->_unregisterPool.push_back(entity);
            }

            bool IsInUnregisterPool(Entity* entity)
            {
                typename std::list<Entity*>::iterator it = this->_unregisterPool.begin();
                typename std::list<Entity*>::iterator itEnd = this->_unregisterPool.end();
                for (; it != itEnd; ++it)
                    if (*it == entity)
                        return true;
                return false;
            }

            void Run(float time)
            {
                this->_interactionManager.SwapWriteBuffers();
                this->_interactionManager.ClearInteractions();
                this->_interactionManager.SwapWriteBuffers();
                typename std::list<Entity*>::iterator it = this->_entities.begin();
                typename std::list<Entity*>::iterator itEnd = this->_entities.end();
                for (; it != itEnd; ++it)
                    if (!this->IsInUnregisterPool(*it))
                        (*it)->GenerateInteractions(time);

                this->_interactionManager.SwapReadBuffers();
                this->_interactionManager.SwapWriteBuffers();
                it = this->_entities.begin();
                itEnd = this->_entities.end();
                for (; it != itEnd; ++it)
                    if (!this->IsInUnregisterPool(*it))
                        (*it)->Run(time);
                this->_ProcessUnregisterPool();
                this->_ProcessRegisterPool();
            }

            InteractionManager<Entity>& GetInteractionManager()
            {
                return this->_interactionManager;
            }

        private:
            void _ProcessRegisterPool()
            {
                typename std::list<Entity*>::iterator it = this->_registerPool.begin();
                typename std::list<Entity*>::iterator itEnd = this->_registerPool.end();
                for (; it != itEnd; ++it)
                    this->_entities.push_back(*it);
                this->_registerPool.clear();
            }

            void _ProcessUnregisterPool()
            {
                typename std::list<Entity*>::iterator it = this->_unregisterPool.begin();
                typename std::list<Entity*>::iterator itEnd = this->_unregisterPool.end();
                for (; it != itEnd; ++it)
                    this->_entities.remove(*it);
                this->_unregisterPool.clear();
            }

            BasicGame<Entity, Player>& _game;
            InteractionManager<Entity> _interactionManager;
            std::list<Entity*> _entities;
            std::list<Entity*> _registerPool;
            std::list<Entity*> _unregisterPool;
        };

    }
}

#endif

