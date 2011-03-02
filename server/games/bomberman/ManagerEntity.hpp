#ifndef __MANAGERENTITY_HPP__
#define __MANAGERENTITY_HPP__

#include <vector>
#include "Entity.hpp"
#include "Item.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ManagerEntity :
            public Entity
        {
            public:
                explicit ManagerEntity(Game& game);
                ~ManagerEntity();
                virtual void Run(float time);

            private:
                struct Score
                {
                    Item* icon;
                    TextEntity<Entity, Game>* nick;
                    int score;
                    TextEntity<Entity, Game>* scoreText;
                };

                void _ClearPanel();
                void _UpdatePanel();
                void _SpawnPlayers();
                void _SpawnMap();
                void _DestroyMap();
                void _RestartMusic();
                Item _bg;
                Item _music;
                bool _started;
                size_t _lastNbOfPlayers;
                std::list<Score*> _scores;
                float _spawnStart;
                bool _mapDestroyed;
                InteractionPtr _bombInteraction;
                std::vector< std::pair<int, int> > _spawns;
        };

    }
}

#endif

