#ifndef __BUTTONENTITY_HPP__
#define __BUTTONENTITY_HPP__

#include "Entity.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ButtonEntity : public Entity
        {
            public:
                explicit ButtonEntity(Game& game, uint16_t playerId);
                ~ButtonEntity();
                void Run(float time);
                void SetPosition(float x, float y, uint8_t z = 128);
                void SetText(String const& text);
                bool Clicked() const;
            private:
                bool _Hover();
                TextEntity<Entity, Game>* _text;
                float _x;
                float _y;
                uint8_t _z;
                size_t _width;
                bool _hover;
                bool _clicked;
                Item _icon;
        };

    }
}

#endif

