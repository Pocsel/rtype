#ifndef __ROOMENTITY_HPP__
#define __ROOMENTITY_HPP__

#include <list>
#include "GameEntity.hpp"
#include "Item.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class BackgroundEntity;

        class RoomEntity : public GameEntity
        {
        public:
            explicit RoomEntity(Game& game);
            ~RoomEntity(void);
            virtual void Run(float time);

        private:
            void _RefreshList();
            void _ClearList();
            Item _listBg;
            Item _start;
            size_t _lastPlayerCount;
            std::list<TextEntity<GameEntity, Game>*> _players;
        };

    }
}

#endif

