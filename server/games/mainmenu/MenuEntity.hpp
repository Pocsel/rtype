#ifndef __MENUENTITY_HPP__
#define __MENUENTITY_HPP__

#include <map>
#include "Entity.hpp"
#include "TextEntity.hpp"
#include "ButtonEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MenuEntity : public Entity
        {
            public:
                explicit MenuEntity(Game& game, uint16_t playerId, String const& nick);
                ~MenuEntity();
                void Run(float time);
            private:
                TextEntity<Entity, Game>* _text;
                std::map<uint16_t, ButtonEntity*> _buttons;
                Item _bg;
                Item _cursor;
                std::map<uint16_t, IGame*> const* _gameList;
        };

    }
}

#endif

