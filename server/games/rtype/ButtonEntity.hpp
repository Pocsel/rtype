#ifndef __BUTTONENTITY_HPP__
#define __BUTTONENTITY_HPP__

#include "MenuEntity.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ButtonEntity : public MenuEntity
        {
            public:
                explicit ButtonEntity(MainGame& game, uint16_t playerId);
                ~ButtonEntity();
                void Run(float time);
                void SetPosition(float x, float y, uint8_t z = 128);
                void SetText(String const& text);
                bool Clicked() const;
            private:
                bool _Hover();
                TextEntity<MenuEntity, MainGame>* _text;
                float _x;
                float _y;
                uint8_t _z;
                size_t _width;
                bool _hover;
                bool _clicked;
        };

    }
}

#endif

